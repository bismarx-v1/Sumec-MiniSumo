#!/usr/bin/env python3

"""
`TfLunaI2C`
================================================================================
TF-Luna i2c Driver
Provides access to the TF-Luna distance sensor.

* Author(s): matt comeione
================================================================================
Requires the installation of i2c-tools, or the installation of smbus2 library
from pip.  Testing with smbus2 has not occurred, however, since this is a drop
in replacement for smbus it should theoretically work.

Code is loosely based off of Bud Ryerson's TFLuna-I2C driver written for the
Arduino in C++.  This code can be found on GitHub:

https://github.com/budryerson/TFLuna-I2C

Definitions are a combination of from the C++ code as well as the TF-Luna manual
from Benewake.  Error codes are not in the manual, so they are taken directly
from Bud Ryerson's code - It is unclear how these codes were derived and may be
inaccurate.

The manual indicates that changes do not take effect until they have been saved
and the device has been reboot.  However, as of version 3.3.0, the changing of
the i2c address takes effect immediately.  If older versions do not follow this
behavior, it is likely that another variable will need to be added to hold the
new i2c address so that upon reboot, the device can re-establish communication.
"""
import time
from smbus import SMBus
# use the following for RaspberryPi (smbus2 is used for syntax support on os x)
# from smbus import SMbus


class TfLunaI2C:
    """
    TfLunaI2C class functions as the i2c driver for the TF-Luna Lidar distance
    """
    # TF-Luna Default Settings #
    DEFAULT_I2C_ADDR = 0x10  # default I2C address = 16
    DEFAULT_FPS = 0x64  # default frame-rate = 100fps

    # Register Names and Numbers #
    DIST_LO = 0x00  # R - Unit: cm
    DIST_HI = 0x01  # R
    AMP_LO = 0x02  # R - Amplitude of reading
    AMP_HI = 0x03  # R
    TEMP_LO = 0x04  # R - Unit: 0.01 Celsius
    TEMP_HI = 0x05  # R
    TICK_LO = 0x06  # R - Ticks since startup
    TICK_HI = 0x07  # R
    ERROR_LO = 0x08  # R - Error number
    ERROR_HI = 0x09  # R
    VERSION_REVISION = 0x0A  # R
    VERSION_MINOR = 0x0B  # R
    VERSION_MAJOR = 0x0C  # R
    SERIAL_NUMBER = 0x10  # 0x10 to Ox1D, 14 bytes ASCII Codes
    SIGNATURE = 0x3C  # 4 byte signature

    SAVE_SETTINGS = 0x20  # W -- Write 0x01 to save
    COMMIT = 0x01   # use to write settings
    REBOOT = 0x21   # W -- Write 0x02 to reboot.
                    # Lidar not accessible during few seconds,
                    # then register value resets automatically
    REBOOT_CODE = 0x02

    I2C_ADDR = 0x22  # W/R -- Range 0x08,0x77.
                     # must save setting to retain after reboot.

    MODE = 0x23  # W/R -- 0x00=continuous, 0x01=trigger
    MODE_CONTINUOUS = 0x00
    MODE_TRIGGER = 0x01
    TRIG_ONE_SHOT = 0x24  # W  --  0x01=trigger once (only in trigger mode)

    ENABLED = 0x25  # W/R -- 0x01=enable, 0x00=disable (labeled enable in manual)

    FPS_LO = 0x26  # W/R -- lo byte
    FPS_HI = 0x27  # W/R -- hi byte

    LOW_POWER = 0x28  # W/R -- 0x00-normal, 0x01-low power

    RESTORE_FACTORY_DEFAULTS = 0x29  # W  --  0x01-restore factory settings

    AMP_THR_LO = 0x2A  # W/R Amplitude threshold level
    AMP_THR_HI = 0x2B  # W/R Amplitude threshold level
    DUMMY_DIST_LO = 0x2C  # W/R dummy distance level
    DUMMY_DIST_HI = 0x2D  # W/R dummy distance level
    MIN_DIST_LO = 0x2E  # W/R Minimum distance level in cm
    MIN_DIST_HI = 0x2F  # W/R Minimum distance level in cm
    MAX_DIST_LO = 0x30  # W/R Maximum distance level in cm
    MAX_DIST_HI = 0x31  # W/R Maximum distance level in cm

    # FPS (Low Power Mode) #
    FPS_1 = 0x01
    FPS_2 = 0x02
    FPS_3 = 0x03
    FPS_4 = 0x04
    FPS_5 = 0x05
    FPS_6 = 0x06
    FPS_7 = 0x07
    FPS_8 = 0x08
    FPS_9 = 0x09
    FPS_10 = 0x0A

    # FPS (High Power Mode) #
    FPS_25 = 0x19
    FPS_35 = 0x23
    FPS_50 = 0x32
    FPS_100 = 0x64
    FPS_125 = 0x7D
    FPS_166 = 0xA6
    FPS_250 = 0xFA

    # Error Status Condition definitions #
    ERROR_READY = 0  # no error
    ERROR_SERIAL = 1  # serial timeout
    ERROR_HEADER = 2  # no header found
    ERROR_CHECKSUM = 3  # checksum doesn't match
    ERROR_TIMEOUT = 4  # I2C timeout
    ERROR_PASS = 5  # Reply from some system commands
    ERROR_FAIL = 6  # Reply from some system commands
    ERROR_I2C_READ = 7
    ERROR_I2C_WRITE = 8
    ERROR_I2C_LENGTH = 9
    ERROR_WEAK = 10  # Signal Strength <= 100
    ERROR_STRONG = 11  # Signal Strength saturation
    ERROR_FLOOD = 12  # Ambient Light saturation
    ERROR_MEASURE = 13
    ERROR_INVALID = 14  # Invalid operation sent to sendCommand()

    ERROR_NO_ERROR = 0
    ERROR_WRITE_FAILED = 100
    ERROR_BAD_ADDRESS = 101
    ERROR_BAD_AMP_THRESHOLD = 102
    ERROR_BAD_DIST_RANGE = 103

    TRUE = 0x01
    FALSE = 0x00

    def __init__(self, address=DEFAULT_I2C_ADDR, us=True, bus=1):
        """
        TfLunaI2C constructor
            Initializes all parameters for the device at the provided or default address.
        :param address: byte
            Provide the i2c address, defaults to 0x10 (factory default) if not provided
        :param us: boolean
            Use imperial units for display - defaults to True - Use False for metric
        :param bus: int
            Provide the bus number if different - defaults to 1
        """
        self.address = address
        self.us = us
        self.fps = 0
        self.dist = 0
        self.amp = 0
        self.temp = 0
        self.sn = ''
        self.version = ''
        self.signature = ''
        self.error = 0
        self.ticks = 0
        self.mode = 0
        self.enabled = 0
        self.low_power = 0
        self.amp_threshold = 0
        self.dummy_dist = 0
        self.min_dist = 0
        self.max_dist = 0
        self.bus = bus
        self.i2cbus = SMBus(self.bus)
        self._load_settings(address, us)

    def __str__(self):
        settings = ''
        settings += "address:     " + hex(self.address) + "\n"
        settings += "sn:          " + self.sn + "\n"
        settings += "signature:   " + self.signature + "\n"
        settings += "version:     " + self.version + "\n"
        if self.mode == self.MODE_CONTINUOUS:
            settings += "mode:        Continuous" + "\n"
        else:
            settings += "mode:        Trigger" + "\n"
        if self.enabled == TfLunaI2C.TRUE:
            settings += "enabled:     True" + "\n"
        else:
            settings += "enabled:     False" + "\n"
        if self.low_power == TfLunaI2C.FALSE:
            settings += "power mode:  Normal" + "\n"
        else:
            settings += "power mode:  Low Power" + "\n"
        settings += "fps:         " + str(self.fps) + "Hz\n"
        temp = self.temp * 0.01
        if self.us:
            temp = TfLunaI2C.celsius2fahrenheit(temp)
            settings += "temperature: " + str(temp) + " Fahrenheit\n"
            settings += "amp thresh:  " + str(self.amp_threshold) + "\n"
            dist = TfLunaI2C.centimeters2feet(self.dummy_dist)
            settings += "dummy dist:  " + str(dist) + " ft\n"
            dist = TfLunaI2C.centimeters2feet(self.min_dist)
            settings += "min dist:    " + str(dist) + " ft\n"
            dist = TfLunaI2C.centimeters2feet(self.max_dist)
            settings += "max dist:    " + str(dist) + " ft\n"
            settings += "ticks:       " + str(self.ticks) + "\n"
            dist = TfLunaI2C.centimeters2feet(self.dist)
            settings += "distance:    " + str(dist) + " ft\n"
            settings += "amplitude:   " + str(self.amp) + "\n"
        else:
            settings += "temperature: " + str(temp) + " Celsius\n"
            settings += "amp thresh:  " + str(self.amp_threshold) + "\n"
            settings += "dummy dist:  " + str(self.dummy_dist) + " cm\n"
            settings += "min dist:    " + str(self.min_dist) + " cm\n"
            settings += "max dist:    " + str(self.max_dist) + " cm\n"
            settings += "ticks:       " + str(self.ticks) + "\n"
            settings += "distance:    " + str(self.dist) + " cm\n"
            settings += "amplitude:   " + str(self.amp) + "\n"

        settings += "error:       " + str(self.error) + "\n"
        return settings

    def __len__(self):
        """ Place holder - Don't believe we will need this """

    def __del__(self):
        """ Place holder - Don't believe we will need this """

    @staticmethod
    def centimeters2feet(cm):
        """
        Basic centimeters to feet conversion
        :param cm: int
        :return: float
        Returns the distance in feet as floating point value
        """
        feet = cm * 0.032808398950131
        return feet

    @staticmethod
    def celsius2fahrenheit(celsius):
        """
        Basic celsius to fahrenheit conversion - assumes integer to
        floating point conversion has already been performed (i.e.,
        temp_reading * 0.01)
        :param celsius: float
            Temperature in Celsius
        :return: float
            Temperature in Fahrenheit
        """
        fahrenheit = (1.8 * celsius) + 32.0
        return fahrenheit

    def _load_settings(self, address=DEFAULT_I2C_ADDR, us=True):
        """
        Load settings into object
        :param address: byte
            i2c device address, defaults to 0x10 (factory default)
        :param us: boolean
            Use imperial units of measurement and temperature
        :return: n/a
        """
        self.address = address
        self.us = us
        self.fps = self.read_frame_rate()
        self.dist = 0
        self.amp = 0
        self.temp = 0
        self.sn = self.read_serial_number()
        self.version = self.read_firmware_version()
        self.signature = self.read_signature()
        self.error = self.read_error()
        self.ticks = self.read_ticks()
        self.mode = self.read_mode()
        self.enabled = self.read_enabled()
        self.low_power = self.read_low_power_mode()
        self.amp_threshold = self.read_amp_threshold()
        self.dummy_dist = self.read_dummy_distance()
        self.min_dist = self.read_minimum_distance()
        self.max_dist = self.read_maximum_distance()
        self.read_data()

    def _read_byte(self, register):
        """
        Read byte from specified register
        :param register:
            Provide a register to read one byte from
        :return:
            Returns byte retrieved
        """
        data = 0x00
        try:
            data = self.i2cbus.read_byte_data(self.address, register)
        except:
            print("error reading from: " + hex(register))
        return data

    def _write_byte(self, register, data):
        """
        Write byte to specified register
        :param register: byte
            Address to write the byte to
        :param data: byte
            byte to write
        :return:
            Error code
        """
        try:
            self.i2cbus.write_byte_data(self.address, register, data)
        except:
            print("error writing " + hex(data) + " to register " + hex(register))
            return TfLunaI2C.ERROR_WRITE_FAILED
        return TfLunaI2C.ERROR_NO_ERROR

    def _read_word(self, register):
        """
        Read word from specified register
        :param register: byte
            Provide a register to read the 2 bytes from
        :return: uint16
            Returns word received.
        """
        data = 0x0000
        try:
            data = self.i2cbus.read_word_data(self.address, register)
        except:
            print("error reading from: " + hex(register))
        return data

    def _write_word(self, register, data):
        """
        Write word to specified register
        :param register: byte
            Address to write the word to
        :param data: int
            Int to write to device
        :return: int
            Error code
        """
        try:
            self.i2cbus.write_word_data(self.address, register, data)
        except:
            print("error writing " + hex(data) + " to register " + hex(register))
            return TfLunaI2C.ERROR_WRITE_FAILED
        return TfLunaI2C.ERROR_NO_ERROR

    def read_firmware_version(self):
        """
        Read firmware version
        :return: string
            Returns full version string in #.#.# format
        """
        major = self._read_byte(TfLunaI2C.VERSION_MAJOR)
        minor = self._read_byte(TfLunaI2C.VERSION_MINOR)
        revision = self._read_byte(TfLunaI2C.VERSION_REVISION)
        return str(major) + "." + str(minor) + "." + str(revision)

    def read_serial_number(self):
        """
        Reads 14 byte production code (serial number) of device
        :return: string
            Returns string representation of serial number
        """
        snlist = []
        register = TfLunaI2C.SERIAL_NUMBER
        for i in range(14):
            snlist.append(self._read_byte(register))
            register += 1
        sn = ''
        for c in snlist:
            sn = sn + chr(c)
        return sn

    def read_frame_rate(self):
        """
        Reads frame rate from registers
        :return: int
            Returns frame rate as integer
        """
        frame_rate = self._read_word(TfLunaI2C.FPS_LO)
        return frame_rate

    def write_frame_rate(self, frame_rate):
        """
        Writes frame rate to memory - requires save and reboot to take effect
        Valid rates are from 1Hz - 250Hz.  Low power mode range is from 1-10Hz.
        Calculated rates are from 500/n Hz where n is an int between 2-500
        :param frame_rate: int
            Frame rate to be set
        :return: int
            Error code
        """
        error = self._write_word(TfLunaI2C.FPS_LO, frame_rate)
        return error

    def set_frame_rate(self, frame_rate):
        """
        Writes frame rate to memory - requires save and reboot to take effect
        Valid rates are from 1Hz - 250Hz.  Low power mode range is from 1-10Hz.
        Calculated rates are from 500/n Hz where n is an int between 2-500
        :param frame_rate: int
            Frame rate to be set
        :return: int
            Error code
        """
        error = self.write_frame_rate(frame_rate)
        return error

    def read_ticks(self):
        """
        Read ticks from device
        :return: int
            Returns ticks since start
        """
        ticks = self._read_word(TfLunaI2C.TICK_LO)
        return ticks

    def read_error(self):
        """
        Read error from device
        :return: int
            Returns error code from device
        """
        error = self._read_word(TfLunaI2C.ERROR_LO)
        return error

    def read_mode(self):
        """
        Read current device mode (continuous or triggered)
        :return: byte
            Returns mode as byte:
                0x00 == Continuous
                0X01 == Triggered
        """
        mode = self._read_byte(TfLunaI2C.MODE)
        return mode

    def write_mode(self, mode):
        """
        Write mode to device (continuous or triggered)
        :param mode: byte
            TfLunaI2C.MODE_CONTINUOUS or
            TfLunaI2C.MODE_TRIGGER
        :return: int
            Returns error code from device
        """
        error = self._write_word(TfLunaI2C.MODE, mode)
        return error

    def set_mode_triggered(self):
        """
        Set to trigger mode
        :return: int
            Returns error code
        """
        error = self.write_mode(TfLunaI2C.MODE_TRIGGER)
        return error

    def set_mode_continuous(self):
        """
        Set to continuous mode
        :return: int
            Returns error code
        """
        error = self.write_mode(TfLunaI2C.MODE_CONTINUOUS)
        return error

    def trigger(self):
        """
        Trigger reading
        :return: int
            Returns error code
        """
        error = self._write_byte(TfLunaI2C.TRIG_ONE_SHOT, TfLunaI2C.TRUE)
        return error

    def read_low_power_mode(self):
        """
        Read low power mode setting from device
        :return: byte
            Returns 0x00 for normal mode, or 0x01 for low power mode
        """
        mode = self._read_byte(TfLunaI2C.LOW_POWER)
        return mode

    def write_low_power_mode(self, mode):
        """
        Writes low power mode setting to device
        :param mode: byte
            Either 0x00 for normal mode or 0x01 for low power mode
            If system is set to low power mode, frame rate should
            be set to an appropriate value (1-10Hz)
        :return: int
            Error code
        """
        error = self._write_byte(TfLunaI2C.MODE, mode)
        return error

    def set_low_power_mode(self):
        """
        Sets device into low power mode
        :return: int
            Returns error code
        """
        error = self.write_low_power_mode(TfLunaI2C.TRUE)
        return error

    def read_amp_threshold(self):
        """
        Read amplitude threshold from device
        :return: int
            Return amplitude threshold value
        """
        amp = self._read_word(TfLunaI2C.AMP_THR_LO)
        return amp

    def write_amp_threshold(self, amp):
        """
        Write setting for amplitude threshold for device.  When this
        amplitude is below this threshold, the dummy distance value is
        returned instead of the device reading.
        :param amp: int
            Integer representing the threshold
        :return: int
            Returns error code
        """
        error = self._write_word(TfLunaI2C.AMP_THR_LO, amp)
        return error

    def set_amp_threshold(self, amp):
        """
        Sets amplitude threshold - checks for valid range
        :param amp: int
             Amplitude threshold to set to.  Valid range 0-32768
        :return: int
            Returns Error Code
        """
        if 0 <= amp <= 32768:
            error = self.write_amp_threshold(amp)
        else:
            error = TfLunaI2C.ERROR_BAD_AMP_THRESHOLD
        return error

    def read_dummy_distance(self):
        """
        Reads dummy distance setting from device
        :return: int
            Returns distance setting used when amplitude threshold is not met.
            Distance is in cm.
        """
        distance = self._read_word(TfLunaI2C.DUMMY_DIST_LO)
        return distance

    def write_dummy_distance(self, distance):
        """
        Writes dummy distance to device
        :param distance: int
            Writes dummy distance to device.  Setting is in cm.
        :return: int
            Error code
        """
        error = self._write_word(TfLunaI2C.DUMMY_DIST_LO, distance)
        return error

    def set_dummy_distance(self, distance):
        """
        Set dummy distance - valid range 0-65536 with a default to 0
        :param distance: int
            Distance to set for low amplitudes
        :return: int
            Returns error code
        """
        error = self.write_dummy_distance(distance)
        return error

    def read_minimum_distance(self):
        """
        Read minimum distance setting from device
        :return: int
            Returns minimum distance setting
        """
        distance = self._read_word(TfLunaI2C.MIN_DIST_LO)
        return distance

    def write_minimum_distance(self, distance):
        """
        Writes minimum distance setting to device
        :param distance: int
            distance in cm to write to device
        :return: int
            Returns error code
        """
        error = self._write_word(TfLunaI2C.MIN_DIST_LO, distance)
        return error

    def read_maximum_distance(self):
        """
        Read maximum distance setting from device
        :return: int
            Returns maximum distance setting
        """
        distance = self._read_word(TfLunaI2C.MAX_DIST_LO)
        return distance

    def write_maximum_distance(self, distance):
        """
        Writes maxi distance setting to device
        :param distance: int
            distance in cm to write to device
        :return: int
            Returns error code
        """
        error = self._write_word(TfLunaI2C.MAX_DIST_LO, distance)
        return error

    def set_distance_limits(self, minimum, maximum):
        """
        Sets the minimum and maximum distance settings in centimeters
        :param minimum: int
            Minimum distance
        :param maximum: int
            Maximum distance
        :return: int
            Returns error code
        """
        if maximum <= minimum:
            return TfLunaI2C.ERROR_BAD_DIST_RANGE
        error = self.write_minimum_distance(minimum)
        if error != 0:
            return error
        error = self.write_maximum_distance(maximum)
        return error

    def read_enabled(self):
        """
        Reads enabled status 0x01 enabled, 0x00 disabled - version A05 of manual
        shows the corrected values for this setting
        :return: byte
            Returns enabled or disabled (i.e., true or false)
        """
        enabled = self._read_byte(TfLunaI2C.ENABLED)
        return enabled

    def write_enabled(self, enabled):
        """
        Writes enabled status to device - set to 0x01 to enable and 0x00 to disable.
        Manuals prior to A05 have these settings incorrect
        :param enabled: byte
            Set to 0x01 to enable and 0x00 to disable Lidar on the device
        :return: int
            Error code
        """
        error = self._write_byte(TfLunaI2C.ENABLED, enabled)
        return error

    def set_enabled(self):
        """
        Sets device to enabled
        :return: int
            Returns error code
        """
        error = self.write_enabled(TfLunaI2C.TRUE)
        return error

    def set_disabled(self):
        """
        Sets device to disabled
        :return: int
            Returns error code
        """
        error = self.write_enabled(TfLunaI2C.FALSE)
        return error

    def read_address(self):
        """
        Read i2c address from device.
        :return: byte
            Returns the i2c address as byte
        """
        address = self._read_byte(TfLunaI2C.I2C_ADDR)
        return address

    def write_address(self, address):
        """
        Writes i2c address to device.  In testing, address changes immediately
        :param address: byte
            Address between 0x08 - 0x77 are valid addresses for this device.
        :return: int
            Returns error code
        """
        if (address < 0x08) or (address > 0x77):
            print("Invalid address provided: " + hex(address))
            print("Valid addresses are 0x08 - 0x77")
            return TfLunaI2C.ERROR_BAD_ADDRESS
        error = self._write_byte(TfLunaI2C.I2C_ADDR, address)
        # Stage new address for reboot
        self.address = address
        return error

    def read_data(self):
        """
        Reads data set from device, includes the following components:
            distance, amplitude, temperature, ticks, error
        :return: list
            returns list of component values
        """
        data = []
        distance = self._read_word(TfLunaI2C.DIST_LO)
        amplitude = self._read_word(TfLunaI2C.AMP_LO)
        temperature = self._read_word(TfLunaI2C.TEMP_LO)
        ticks = self._read_word(TfLunaI2C.TICK_LO)
        error = self._read_word(TfLunaI2C.ERROR_LO)
        data.append(distance)
        data.append(amplitude)
        data.append(temperature)
        data.append(ticks)
        data.append(error)
        self.dist = distance
        self.amp = amplitude
        self.temp = temperature
        self.ticks = ticks
        self.error = error
        return data

    def print_data(self):
        """
        Prints data from last read
        :return: n/a
        """
        print("----------------------------------------")
        temp = self.temp * 0.01

        if self.us:
            dist = TfLunaI2C.centimeters2feet(self.dist)
            print("distance:    " + str(dist) + "ft")
            print("amplitude:   " + str(self.amp))
            temp = TfLunaI2C.celsius2fahrenheit(temp)
            print("temperature: " + str(temp) + " Fahrenheit")
            print("ticks:       " + str(self.ticks))
            print("error:       " + str(self.error))
        else:
            print("distance:    " + str(self.dist) + "cm")
            print("amplitude:   " + str(self.amp))
            print("temperature: " + str(temp) + " Celsius")
            print("ticks:       " + str(self.ticks))
            print("error:       " + str(self.error))

    def read_distance(self):
        """
        Read distance
        :return: int
            Returns distance in cm.
        """
        distance = self._read_word(TfLunaI2C.DIST_LO)
        return distance

    def read_amplitude(self):
        """
        Reads amplitude - Amplitude should be over 100 but less than 30,000
        Under 100 the signal is too low to be accurate.  Above 30000 the ambient
        lighting is probably too high (i.e. direct sunlight).
        :return: int
            Returns amplitude as integer
        """
        amplitude = self._read_word(TfLunaI2C.AMP_LO)
        return amplitude

    def read_temperature(self):
        """
        Reads temperature from device - temperature of chip is indicated in Celsius
        Multiply the integer value returned by 0.01 to get the degrees in Celsius
        :return: int
            Returns raw integer temperature value from device
        """
        temperature = self._read_word(TfLunaI2C.TEMP_LO)
        return temperature

    def save(self):
        """
        Saves settings to device
        :return: int
            Returns error code
        """
        error = self._write_byte(TfLunaI2C.SAVE_SETTINGS, TfLunaI2C.COMMIT)
        return error

    def reboot(self):
        """
        Reboots device, process will likely take a few seconds to complete.
        If the i2c address has been changed, the address will be updated to
        the new expected address after the reboot command has been issued.
        :return: int
            Returns error code
        """
        error = self._write_byte(TfLunaI2C.REBOOT, TfLunaI2C.REBOOT_CODE)
        return error

    def factory_reset(self):
        """
        Resets device to factory defaults
        :return: int
            Returns error code
        """
        error = self._write_byte(TfLunaI2C.RESTORE_FACTORY_DEFAULTS, TfLunaI2C.TRUE)
        self.reboot()
        print("Resetting to factory defaults")
        time.sleep(1)
        self.address = TfLunaI2C.DEFAULT_I2C_ADDR
        self._load_settings(self.address, self.us)
        return error

    def read_signature(self):
        """
        Reads signature from device
        :return: string
            Returns signature string
        """
        signature_list = []
        register = TfLunaI2C.SIGNATURE
        for i in range(4):
            signature_list.append(self._read_byte(register))
            register += 1
        signature = ''
        for c in signature_list:
            signature = signature + chr(c)
        return signature