#include "kame.h"

void Kame::init(){    
    board_pins[0] = SERVO_0_PIN;
    board_pins[1] = SERVO_1_PIN;
    board_pins[2] = SERVO_2_PIN;
    board_pins[3] = SERVO_3_PIN;
    board_pins[4] = SERVO_4_PIN;
    board_pins[5] = SERVO_5_PIN;
    board_pins[6] = SERVO_6_PIN;
    board_pins[7] = SERVO_7_PIN;

    servoHandler = ServoHandler(board_pins);
    home();
}

void Kame::execute(float steps, int period[8], int amplitude[8], int offset[8], int phase[8]){
/*
    for (int i=0; i<8; i++){
        oscillator[i].setPeriod(period[i]);
        oscillator[i].setAmplitude(amplitude[i]);
        oscillator[i].setPhase(phase[i]);
        oscillator[i].setOffset(offset[i]);
    }

    unsigned long global_time = millis();

    for (int i=0; i<8; i++) oscillator[i].setTime(global_time);

    _final_time = millis() + period[0]*steps;
    while (millis() < _final_time){
        for (int i=0; i<8; i++){
            servoHandler.move(i, oscillator[i].refresh());
        }
        yield();
    }
        */
}

void Kame::turnR(float steps, int T=600){
    int x_amp = 15;
    int z_amp = 15;
    int ap = 15;
    int hi = 23;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    int phase[] = {0,180,90,90,180,0,90,90};

    execute(steps, period, amplitude, offset, phase);
}

void Kame::turnL(float steps, int T=600){
    int x_amp = 15;
    int z_amp = 15;
    int ap = 15;
    int hi = 23;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    int phase[] = {180,0,90,90,0,180,90,90};

    execute(steps, period, amplitude, offset, phase);
}

void Kame::dance(float steps, int T=600){
    int x_amp = 0;
    int z_amp = 40;
    int ap = 30;
    int hi = 20;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    int phase[] = {0,0,0,270,0,0,90,180};

    execute(steps, period, amplitude, offset, phase);
}

void Kame::frontBack(float steps, int T=600){
    int x_amp = 30;
    int z_amp = 25;
    int ap = 20;
    int hi = 30;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    int phase[] = {0,180,270,90,0,180,90,270};

    execute(steps, period, amplitude, offset, phase);
}

void Kame::run(float steps, int T=5000){
    int x_amp = 15;
    int z_amp = 15;
    int ap = 15;
    int hi = 15;
    int front_x = 6;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {    90+ap-front_x,
                        90-ap+front_x,
                        90-hi,
                        90+hi,
                        90-ap-front_x,
                        90+ap+front_x,
                        90+hi,
                        90-hi
                    };
    int phase[] = {0,0,90,90,180,180,90,90};

    execute(steps, period, amplitude, offset, phase);
}

void Kame::omniWalk(float steps, int T){
    int x_amp = 0;
    int z_amp = 20;
    int ap = 20;
    int hi = 10;
    int front_x = 12;
    int period[] = {T, T, T/2, T/2, T, T, T/2, T/2};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {    90+ap,
                        90-ap,
                        90-hi,
                        90+hi,
                        90-ap,
                        90+ap,
                        90+hi,
                        90-hi
                    };
    int  phase[] = {90, 90, 270, 90, 270, 270, 90, 270};

    for (int i=0; i<8; i++){
        oscillator[i].reset();
        oscillator[i].setPeriod(period[i]);
        oscillator[i].setAmplitude(amplitude[i]);
        oscillator[i].setPhase(phase[i]);
        oscillator[i].setOffset(offset[i]);
    }

    _final_time = millis() + period[0]*steps;
    _init_time = millis();
    bool side;
    while (millis() < _final_time){
        side = (int)((millis()-_init_time) / (period[0]/2)) % 2;
        servoHandler.move(0, oscillator[0].refresh());
        servoHandler.move(1, oscillator[1].refresh());
        servoHandler.move(4, oscillator[4].refresh());
        servoHandler.move(5, oscillator[5].refresh());

        if (side == 0){
            servoHandler.move(3, oscillator[3].refresh());
            servoHandler.move(6, oscillator[6].refresh());
        }
        else{
            servoHandler.move(2, oscillator[2].refresh());
            servoHandler.move(7, oscillator[7].refresh());
        }
        delay(1);
    }
}

void Kame::moonwalkL(float steps, int T=5000){
    int z_amp = 45;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {0,0,z_amp,z_amp,0,0,z_amp,z_amp};
    int offset[] = {90, 90, 90, 90, 90, 90, 90, 90};
    int phase[] = {0,0,0,120,0,0,180,290};

    execute(steps, period, amplitude, offset, phase);
}

void Kame::walk(float steps, int T=5000){
    int x_amp = 15;
    int z_amp = 20;
    int ap = 20;
    int hi = 10;
    int front_x = 12;
    int period[] = {T, T, T/2, T/2, T, T, T/2, T/2};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {    90+ap-front_x,
                        90-ap+front_x,
                        90-hi,
                        90+hi,
                        90-ap-front_x,
                        90+ap+front_x,
                        90+hi,
                        90-hi
                    };
    int  phase[] = {90, 90, 270, 90, 270, 270, 90, 270};

    for (int i=0; i<8; i++){
        oscillator[i].reset();
        oscillator[i].setPeriod(period[i]);
        oscillator[i].setAmplitude(amplitude[i]);
        oscillator[i].setPhase(phase[i]);
        oscillator[i].setOffset(offset[i]);
    }

    _final_time = millis() + period[0]*steps;
    _init_time = millis();
    bool side;
    while (millis() < _final_time){
        side = (int)((millis()-_init_time) / (period[0]/2)) % 2;
        servoHandler.move(0, oscillator[0].refresh());
        servoHandler.move(1, oscillator[1].refresh());
        servoHandler.move(4, oscillator[4].refresh());
        servoHandler.move(5, oscillator[5].refresh());

        if (side == 0){
            servoHandler.move(3, oscillator[3].refresh());
            servoHandler.move(6, oscillator[6].refresh());
        }
        else{
            servoHandler.move(2, oscillator[2].refresh());
            servoHandler.move(7, oscillator[7].refresh());
        }
        delay(1);
    }
}

void Kame::backward(float steps, int T=5000){
    int x_amp = 15;
    int z_amp = 20;
    int ap = 20;
    int hi = 10;
    int front_x = -12;
    int period[] = {T, T, T/2, T/2, T, T, T/2, T/2};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {    90+ap-front_x,
                        90-ap+front_x,
                        90-hi,
                        90+hi,
                        90-ap-front_x,
                        90+ap+front_x,
                        90+hi,
                        90-hi
                    };
    int  phase[] = {270, 270, 270, 90, 90, 90, 90, 270};

    for (int i=0; i<8; i++){
        oscillator[i].reset();
        oscillator[i].setPeriod(period[i]);
        oscillator[i].setAmplitude(amplitude[i]);
        oscillator[i].setPhase(phase[i]);
        oscillator[i].setOffset(offset[i]);
    }

    _final_time = millis() + period[0]*steps;
    _init_time = millis();
    bool side;
    while (millis() < _final_time){
        side = (int)((millis()-_init_time) / (period[0]/2)) % 2;
        servoHandler.move(0, oscillator[0].refresh());
        servoHandler.move(1, oscillator[1].refresh());
        servoHandler.move(4, oscillator[4].refresh());
        servoHandler.move(5, oscillator[5].refresh());

        if (side == 0){
            servoHandler.move(3, oscillator[3].refresh());
            servoHandler.move(6, oscillator[6].refresh());
        }
        else{
            servoHandler.move(2, oscillator[2].refresh());
            servoHandler.move(7, oscillator[7].refresh());
        }
        delay(1);
    }
}

void Kame::upDown(float steps, int T=5000){
    int x_amp = 0;
    int z_amp = 35;
    int ap = 20;
    int hi = 25;
    int front_x = 0;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {    90+ap-front_x,
                        90-ap+front_x,
                        90-hi,
                        90+hi,
                        90-ap-front_x,
                        90+ap+front_x,
                        90+hi,
                        90-hi
                    };
    int phase[] = {0,0,90,270,180,180,270,90};

    execute(steps, period, amplitude, offset, phase);
}

void Kame::pushUp(float steps, int T=600){
    int z_amp = 40;
    int x_amp = 65;
    int hi = 30;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {0,0,z_amp,z_amp,0,0,0,0};
    int offset[] = {90,90,90-hi,90+hi,90-x_amp,90+x_amp,90+hi,90-hi};
    int phase[] = {0,0,0,180,0,0,0,180};

    execute(steps, period, amplitude, offset, phase);
}

void Kame::hello(){
    float sentado[]={90+15,90-15,90-65,90+65,90+20,90-20,90+10,90-10};
    moveServos(150, sentado);
    delay(200);

    int z_amp = 40;
    int x_amp = 60;
    int T=350;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {0,50,0,50,0,0,0,0};
    int offset[] = {90+15,40,90-65,90,90+20,90-20,90+10,90-10};
    int phase[] = {0,0,0,90,0,0,0,0};

    execute(4, period, amplitude, offset, phase);

    float goingUp[]={160,20,90,90,90-20,90+20,90+10,90-10};
    moveServos(500, goingUp);
    delay(200);
}

void Kame::jump(){
    float sentado[]={90+15,90-15,90-65,90+65,90+20,90-20,90+10,90-10};
    float ap = 20.0;
    float hi = 35.0;
    float salto[] = {90+ap,90-ap,90-hi,90+hi,90-ap*3,90+ap*3,90+hi,90-hi};
    moveServos(150, sentado);
    delay(200);
    moveServos(0, salto);
    delay(100);
    home();
}

void Kame::home(){
    int ap = 20;
    int hi = 35;
    int position[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    for (int i=0; i<8; i++) servoHandler.move(i, position[i]);
}

void Kame::zero(){
    for (int i=0; i<8; i++) servoHandler.move(i, 90);
}
