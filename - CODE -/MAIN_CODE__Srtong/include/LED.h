#ifndef _LED_H
#define _LED_H

#include <Arduino.h>

/**
 * @brief LED class to control LED in variuous modes.
 */
class LED {

    private:

        uint32_t mLastMillis;
        uint8_t mMode;
        uint8_t mLastMode;
        uint8_t mStatus;
        uint8_t mPin;
        uint32_t mTimeOn;
        uint32_t mTimeOff;

    public:
        /**
         * Create a new LED object.
         * @brief Default constructor.
         * @see LED(uint8_t pin)
         */
        LED();

        /**
         * Construct a new LED object.
         * @brief Copy constructor.
         * @param pin Pin number of LED.
         * @see LED()
         */
        LED(uint8_t pin);

        /**
         * @brief Initialize LED class with chosen pin.
         * @param pin Pin number of LED.
        */  
        void begin(uint8_t pin);

        /**
         * @brief Blinks LED symmetrically.
         * @param time Desired time in [ms] of ON/OFF-state.
        */        
        void blink(uint32_t time);

        /**
         * @brief Blinks LED asymmetrically.
         * @param onTime Desired time in [ms] of ON-state.
         * @param offTime Desired time in [ms] of OFF-state.
        */   
        void blink(uint32_t onTime, uint32_t offTime);

        /**
         * @brief Updates LED timers and tracks chosen mode.
        */
        void update();

        /**
         * @brief Turns LED ON.
        */
        void setOn();

        /**
         * @brief Turns LED OFF.
        */
        void setOff();

};

LED::LED() {

}

LED::LED(uint8_t pin) {

    begin(pin);

}

void LED::begin(uint8_t pin) {

    pinMode(pin, OUTPUT);
    mPin = pin;
    mMode = 0;

}

void LED::setOn() {

    mMode = 1;

}

void LED::setOff() {

    mMode = 0;

}

void LED::blink(uint32_t time) {

    mTimeOn = time;
    mMode = 2;

}

void LED::blink(uint32_t timeOn, uint32_t timeOff) {

    mTimeOn = timeOn;
    mTimeOff = timeOff;
    mMode = 3;

}

void LED::update() {

    switch (mMode) {

        case 0:
            mStatus = 0;
            break;
        case 1:
            mStatus = 1;
            break;
        case 2:
            if (mLastMode != mMode) mLastMillis = millis() + mTimeOn;
            if (millis() - mLastMillis >= mTimeOn) {
                if (mStatus == 1) mStatus = 0;
                else mStatus = 1;
                mLastMillis = millis();
            }
            break;
        case 3:
            if (mLastMode != mMode) {
                mLastMillis = millis() + mTimeOn;
                mStatus = 1;
            }
            if (mStatus == 1 && (millis() - mLastMillis > mTimeOn)) {
                mStatus = 0;
                mLastMillis = millis();
            } else if (mStatus == 0 && (millis() - mLastMillis > mTimeOff)) {
                mStatus = 1;
                mLastMillis = millis();
            }
            break;
    }

    mLastMode = mMode;

    digitalWrite(mPin, mStatus);

}

#endif