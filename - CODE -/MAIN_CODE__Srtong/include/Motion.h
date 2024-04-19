#ifndef MOTION_H
#define MOTION_H

#include <Motor.h>

/**
 * @brief Motion class to move the robot forward/backward/left/right with given velocity.
 */
class Motion {

    private:
        Motor mLMotor;
        Motor mRMotor;
        float limitRange(float value, const float min, const float max);

    public:
        /**
         * Create a new Motion object.
         * @brief Default constructor.
         * @see Motion(Motor &LMotor, Motor &RMotor)
         */
        Motion();

        /**
         * Construct a new Motion object.
         * @brief Copy constructor.
         * @param LMotor Left motor Motor object.
         * @param RMotor Right motor Motor object.
         * @see Motion()
         */
        Motion(Motor &LMotor, Motor &RMotor);

        /**
         * @brief Moves robot forward.
         * @param speed Desired speed of the robot (between 0.0 and 1.0).
        */
        void goForward(float speed);

        /**
         * @brief Moves robot backward.
         * @param speed Desired speed of the robot (between 0.0 and 1.0).
        * @pre speed hase to be between 0.0 and 1.0.         
        */
        void goBackward(float speed);

        /**
         * @brief Turns robot left at place.
         * @param turning Desired speed of the robot (between 0.0 and 1.0).
        */
        void turnLeft(float turning);

        /**
         * @brief Turns robot right at place.
         * @param turning Desired speed of the robot (between 0.0 and 1.0).
        */
        void turnRight(float turning);

        /**
         * @brief Stops robot.
        */
        void stop();
};

Motion::Motion() {

}

Motion::Motion(Motor &LMotor, Motor &RMotor) {
    mLMotor = LMotor;
    mRMotor = RMotor;

    mLMotor.stop();
    mRMotor.stop();
}

float Motion::limitRange(float value, const float min, const float max) {
    float v;
    if (value > max) {
        v = max;
    } else if (value < min) {
        v = min;
    } else v = value;
    return v;
}

void Motion::turnRight(float turning) {

    float t = limitRange(turning, 0.0, 1.0);
    
    mLMotor.goForward();
    mLMotor.setSpeed(t);
    mRMotor.goBackward();
    mRMotor.setSpeed(t);

}

void Motion::turnLeft(float turning) {

    float t = limitRange(turning, 0.0, 1.0);

    mLMotor.goBackward();
    mLMotor.setSpeed(t);
    mRMotor.goForward();
    mRMotor.setSpeed(t);

}

void Motion::goForward(float speed) {

    float s = limitRange(speed, 0.0, 1.0);

    mLMotor.goForward();
    mLMotor.setSpeed(s);
    mRMotor.goForward();
    mRMotor.setSpeed(s);

}

void Motion::goBackward(float speed) {

    float s = limitRange(speed, 0.0, 1.0);

    mLMotor.goBackward();
    mLMotor.setSpeed(s);
    mRMotor.goBackward();
    mRMotor.setSpeed(s);

}

void Motion::stop() {

    mLMotor.stop();
    mRMotor.stop();

}

#endif