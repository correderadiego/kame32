#ifndef SERVO_H
#define SERVO_H

#include <Arduino.h>
#include <Oscillator.h>

#define SERVO_MIN_ANGLE 0.0f
#define SERVO_MAX_ANGLE 180.0f
#define SERVO_PWM_MIN 1638
#define SERVO_PWM_MAX 8191
#define SERVO_PWM_FREQ 50
#define SERVO_PWM_RES 16

class Servo {
public:
    Servo();
    Servo(int pin, int calibration = 0, bool reversed = false);

    void attach();
    void detach();
    void move(float angle);
    float read();
    void setCalibration(int value);
    int getCalibration();
    void setReverse(bool value);
    bool isReversed();
    int getPin();

    void setIncrement(float value);
    float getIncrement();   

private:
    int _pin;
    int _index;
    int _calibration;
    bool _reversed;
    float _angle;
    bool _attached;
    float _increment;
    Oscillator _oscillator;

    float applyCalibration(float angle);
    float constrainAngle(float value);
    int calculateDuty(float value);
    void writeDuty(int duty);
};

#endif // SERVO_H

