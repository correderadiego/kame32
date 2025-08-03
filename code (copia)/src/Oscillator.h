#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <Arduino.h>
#include <math.h>


class Oscillator {    
public:
    #define DEFAULT_PERIOD 2000
    #define DEFAULT_AMPLITUDE 50
    #define DEFAULT_PHASE 0
    #define DEFAULT_OFFSET 0
    #define DEFAULT_STOP true
    #define DEFAULT_OUTPUT 90

    Oscillator();

    float refresh();
    void reset();
    void start();
    void start(unsigned long ref_time);
    void stop();

    void setPeriod(float period);
    void setAmplitude(float amplitude);
    void setPhase(float phase);
    float getPhase();
    void setOffset(float offset);
    void setTime(unsigned long ref);
    float getOutput();
    unsigned long getTime();
    float getPhaseProgress();

private:
    float time_to_radians(double time);
    float degrees_to_radians(float degrees);
    float degrees_to_time(float degrees);

    float _period;
    float _amplitude;
    float _phase;
    float _offset;
    bool _stop;
    unsigned long _ref_time;
    float _delta_time;
    float _output;
};

#endif // OSCILLATOR_H