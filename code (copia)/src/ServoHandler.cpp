#include "ServoHandler.h"
#include <ArduinoNvs.h>
#include <Servo.h>

ServoHandler::ServoHandler() {}

ServoHandler::ServoHandler(const int pins[NUM_SERVOS]) {
    for (int i = 0; i < NUM_SERVOS; i++) {
        servo[i] = Servo(i, pins[i]);       
    }
}

void ServoHandler::attach(int id) {
    servo[id].attach();
}

void ServoHandler::detach(int id) {
    servo[id].detach();
}

void ServoHandler::setCalibration(int cal[NUM_SERVOS]) {
    for (int i = 0; i < NUM_SERVOS; i++) {        
        servo[i].setCalibration(cal[i]);
    }
}

void ServoHandler::setReverse(int id, bool rev) {   
    servo[id].setReverse(rev);
}

void ServoHandler::move(int id, float angle) {
    servo[id].move(angle);
}

float ServoHandler::read(int id) {
    return servo[id].read();
}

void ServoHandler::move(float servo_position[NUM_SERVOS]) {    
    for (int i = 0; i < NUM_SERVOS; i++){
        servo[i].move(servo_position[i]);
    } 
}

void ServoHandler::moveServos(int ms, float target[NUM_SERVOS]) {    
    if (ms>10){
        for (int i=0; i<NUM_SERVOS; i++)
            servo[i].setIncrement((target[i] - _servo_position[i]) / (ms / 10.0));            

        _final_time = millis() + ms;

        while (millis() < _final_time){
            _partial_time = millis() + 10;
            move(_servo_position);
            while (millis() < _partial_time);
        }
    }
    else{
        move(target);        
    }    
}

void ServoHandler::saveCalibration() {
    if (NVS.begin()) {
        for (int i = 0; i < NUM_SERVOS; i++) {
            NVS.setInt("servo" + String(i), servo[i].getCalibration());
        }
    }
}

void ServoHandler::loadCalibration() {
    if (NVS.begin()) {
        for (int i = 0; i < NUM_SERVOS; i++) {
            servo[i].setCalibration(NVS.getInt("servo" + String(i), 0));            
        }
    }
}