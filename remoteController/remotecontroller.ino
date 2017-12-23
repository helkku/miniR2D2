#include <Wire.h>
#include "nunchuk.h"
#include<SPI.h>
#include<RF24.h>
//ce csn pins
RF24 radio(9,10) ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  //ninchuk_init_power //A1 and A2 is power supplu
  nunchuk_init();
  radio.begin() ;
  //Radio power level
  radio.setPALevel(RF24_PA_MAX); 
  //Channel
  radio.setChannel(0x76) ;
  //pipe to tx to
   radio.openWritingPipe(0xF0F0F0F0E1LL) ;
  radio.enableDynamicPayloads() ;
  radio.powerUp() ;

  //string to send 
  //
}

void loop() {

    if (nunchuk_read()) {
        // Work with nunchuk_data
        String tx = String("X") + String(nunchuk_joystickX()) + String(";Y") + String(nunchuk_joystickY()) + String(";A") + String(nunchuk_joystick_angle()) + String(";Z") + String(nunchuk_buttonZ()) + String(";C") + String(nunchuk_buttonC()) + String(";\n");
        int lenOfTx = tx.length();
        char size_of[tx.length() + 1];
        tx.toCharArray(size_of, sizeof(tx));
        Serial.print(tx);
        radio.write(&tx, lenOfTx);
        /*
        Serial.print(nunchuk_joystickX_raw());
        Serial.print('\n');
        Serial.print(nunchuk_joystickX());
         Serial.print('\n');
         */
       // nunchuk_print();
    }
    delay(100);
}
