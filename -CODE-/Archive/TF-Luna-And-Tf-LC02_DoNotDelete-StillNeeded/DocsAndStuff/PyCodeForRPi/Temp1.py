from TfLunaI2C import TfLunaI2C
import time
if __name__ == '__main__':
    # Basic Usage:
    tf = TfLunaI2C()
    print(tf)
    for i in range(10):
        data = tf.read_data()
        tf.print_data()
        time.sleep(0.5)

    # change to metric
    tf.us = False
    print(tf)
    for i in range(10):
        data = tf.read_data()
        tf.print_data()
        time.sleep(0.5)

    # Change Device i2c Slave Address

    # tf.write_address(0x11)
    # tf.save()
    # tf.reboot()
    # time.sleep(2)
    # print(tf)


    # Change Frame Rate

    # tf.write_frame_rate(TfLunaI2C.FPS_50)
    # tf.save()
    # tf.reboot()
    # time.sleep(2)
    # print(tf)


    # Reset Factory Defaults

    # TODO: test this sequence - may not need to save and reboot
    # Note from NatSi: save and reboot is not needed
    # tf.factory_reset()
    # tf.save()
    # tf.reboot()
    # time.sleep(2)
    # print(tf)


    # Set Trigger Mode

    # tf.set_mode_triggered()
    # tf.save()
    # tf.reboot()
    # time.sleep(2)
    # print(tf)

    # Trigger Reading
    # tf.trigger()
    # Should monitor pin 6 for data ready
    # tf.read_data()
    # tf.print_data()

    # Set Continuous Mode

    # tf.set_mode_continuous()
    # tf.save()
    # tf.reboot()
    # time.sleep(2)
    # print(tf)