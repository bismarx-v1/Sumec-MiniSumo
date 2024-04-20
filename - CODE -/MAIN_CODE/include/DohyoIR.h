#ifndef DOHYO_H
#define DOHYO_H

#include <IRremote.hpp>

#define DECODE_RC5

class DohyoIR {

    private:

        uint16_t mAddress;
        uint16_t mCommand;
        uint16_t mDohyoID;
        uint8_t mStart;
        uint8_t mGotDohyoID;

    public:

        DohyoIR(uint_fast8_t pin);
        void update();
        uint16_t getDohyoID();
        uint8_t isStarted();
        uint8_t isStopped();
        uint8_t hasDohyoID();

};

DohyoIR::DohyoIR(uint_fast8_t pin) {

    IrReceiver.begin(pin);

}

void DohyoIR::update() {

    if (IrReceiver.decode()) {

        if (IrReceiver.decodedIRData.protocol == RC5) {

            IrReceiver.resume();
            IrReceiver.printIRResultShort(&Serial);
            mAddress = IrReceiver.decodedIRData.address;
            mCommand = IrReceiver.decodedIRData.command;

            switch (mAddress) {
                case 0x0B:
                    if (mGotDohyoID == 0) mDohyoID = mCommand & 0xFE;
                    mGotDohyoID = 1;
                    break;
                case 0x07:
                    if ((mCommand & 0xFE) == mDohyoID) {
                        mStart = mCommand & 0x01;
                    }
                    break;
            }
        } else {
            IrReceiver.resume();
        }

    }
}

uint8_t DohyoIR::isStarted() {

    return mStart;

}

uint8_t DohyoID::isStopped() {

    return (mStart == 0);

}

uint16_t DohyoIR::getDohyoID() {

    return mDohyoID;

}

uint8_t DohyoIR::hasDohyoID() {

    return mGotDohyoID;

}

#endif