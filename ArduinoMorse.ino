/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
void transmit(int in[], int length, int factor, int delay);
void markLong(uint16_t time, int div, int delay);
void markShort(uint16_t time, int div, int delay);
void space(uint16_t time, int div, int delay);
uint8_t test[12] = {2 , 1, 2, 1, 0, 2, 2, 1, 2,0,0,0}; // CQ
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  DDRD = B11111100;
  
}

// the loop function runs over and over again forever
void loop() {
  transmit(test, 12, 6,2);
  //markShort(1000,3);
  //space(1000,3);
  delay(100);                       // wait for a second

}

void transmit(uint8_t in[], int length, int factor, int delay){
  for(int i=0; i<length; i++){
    if(in[i] == 2){
      markLong(1000,factor, delay);
      space(1000,factor, delay);
    } else if (in[i] == 1){
      markShort(1000,factor, delay);
      space(1000,factor, delay);
    } else{
      space(1000,factor, delay);
    }
  }
}

void markLong(uint16_t time, int div, int delay){
  for(int q=0; q<div; q++){
    for(int i=0; i<(30*time); i++ ){
    PORTD = PORTD | B10000000;
    //delay(100);                       // wait for a second
      for(int b=0; b<delay; b++){
        asm("NOP");
      }
    PORTD = PORTD & B01111111;
      for(int b=0; b<delay; b++){
        asm("NOP");
      }
    }
  }

}

void markShort(uint16_t time, int div, int delay){
  for(int q=0; q<div; q++){
    for(int i=0; i<(15*time); i++ ){
    PORTD = PORTD | B10000000;
    //delay(100); 
      for(int b=0; b<delay; b++){
        asm("NOP");
      }
    PORTD = PORTD & B01111111;
      for(int b=0; b<delay; b++){
        asm("NOP");
      }
    }
  }

}

void space(uint16_t time, int div, int delay){
  for(int q=0; q<div; q++){
    for(int i=0; i<(30*time); i++ ){
    PORTD = PORTD & B01111111;
      for(int b=0; b<delay; b++){
        asm("NOP");
      }
    PORTD = PORTD & B01111111;
      for(int b=0; b<delay; b++){
        asm("NOP");
      }
    }
  }

}
