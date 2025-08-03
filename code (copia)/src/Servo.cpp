#include "Servo.h"

Servo::Servo(int index, int pin) : _pin(-1), _calibration(0), _reversed(false), _angle(0), _attached(false) {
    _pin = pin;
    _index = index;
    _oscillator.start();    
    attach();
}

Servo::Servo(int pin, int calibration, bool reversed)
    : _pin(pin), _calibration(calibration), _reversed(reversed), _angle(0), _attached(false) {}

void Servo::attach() {    
    _attached = true;
    ledcSetup(_index, SERVO_PWM_FREQ, SERVO_PWM_RES);
    ledcAttachPin(_pin, _index);  
}

void Servo::detach() {
    _attached = false;
    ledcWrite(_index, 0);
}

void Servo::move(float angle) {
    _angle = angle;
    writeDuty(calculateDuty(constrainAngle(applyCalibration(angle))));
}

float Servo::applyCalibration(float angle) {
    return angle + _calibration;
}

float Servo::constrainAngle(float value) {
    return constrain(value, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
}

int Servo::calculateDuty(float value) {
    if (!_reversed)
        return value / SERVO_MAX_ANGLE * (SERVO_PWM_MAX - SERVO_PWM_MIN) + SERVO_PWM_MIN;
    else
        return (SERVO_MAX_ANGLE - value) / SERVO_MAX_ANGLE * (SERVO_PWM_MAX - SERVO_PWM_MIN) + SERVO_PWM_MIN;
}

void Servo::writeDuty(int duty) {
    ledcWrite(_pin, duty);
}

float Servo::read() {
    return _angle;
}

void Servo::setCalibration(int value) {
    _calibration = value;
}

int Servo::getCalibration() {
    return _calibration;
}

void Servo::setReverse(bool value) {
    _reversed = value;
}

bool Servo::isReversed() {
    return _reversed;
}

int Servo::getPin() {
    return _pin;
}

void Servo::setIncrement(float value) {
    _increment = value;
}

float Servo::getIncrement() {
    return _increment;
}