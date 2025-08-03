#ifndef SERVOHANDLER_H
#define SERVOHANDLER_H

#include <Arduino.h>
#include <ArduinoNvs.h>
#include <Servo.h>

#define NUM_SERVOS 8

class ServoHandler {
public:
    ServoHandler(const int pins[NUM_SERVOS]);
    void attach(int id);
    void detach(int id);
    void setCalibration(int cal[NUM_SERVOS]);
    void setReverse(int id, bool rev);
    void move(int id, float angle);
    
    float read(int id);

    void saveCalibration();
    void loadCalibration();
    void moveServos(float _servo_position[NUM_SERVOS]);
    void moveServosDelayed(int ms, float target[NUM_SERVOS]); 

private:

    Servo* servo[NUM_SERVOS];
    float _increment[NUM_SERVOS];
    float _servo_position[NUM_SERVOS];  
    unsigned long _init_time;
    unsigned long _final_time;
    unsigned long _partial_time;
};

#endif // SERVOHANDLER_H