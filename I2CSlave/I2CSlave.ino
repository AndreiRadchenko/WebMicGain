#include "MicRemote.h"
#include "stdio.h"
#include "stdlib.h"

#define SERIAL_BAUD 115200
#define DEBUG
//byte mic_config_set;
//unsigned char ccu_ch[24]; // global array for saving gain value
//char ccu_name[12][16];    //string array for ccu names. names length is 16 char
char ccu[] = "00";
int ccu_num = 0;
unsigned char mic1;
unsigned char mic2;

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {

  ccu[0] = Wire.read();
  ccu[1] = Wire.read();
  mic1 = Wire.read();    // receive byte as an integer
  mic2 = Wire.read();

  ccu_num = atoi (ccu);
  
  switch (ccu_num)
          {
            case 11:
                  gain_change_ccu(CCU1_out, mic1, mic2); //set gpio on appopriate port 
                  break;
            case 12:
                  gain_change_ccu(CCU2_out, mic1, mic2); //set gpio on appopriate port  
                  break;
            case 13:
                  gain_change_ccu(CCU3_out, mic1, mic2); //set gpio on appopriate port  
                  break;
            case 14:
                  gain_change_ccu(CCU4_out, mic1, mic2); //set gpio on appopriate port  
                  break;
            case 15:
                  gain_change_ccu(CCU5_out, mic1, mic2); //set gpio on appopriate port  
                  break;
            case 16:
                  gain_change_ccu(CCU6_out, mic1, mic2); //set gpio on appopriate port  
                  break;                          
            default:
                  break;
          };

  #ifdef DEBUG
      Serial.print("CCU");         
      Serial.print(ccu_num); 
      //Serial.print(ccu[1]);
      Serial.print(" mic1: ");  
      Serial.print(mic1); 
      Serial.print(" mic2: ");  
      Serial.println(mic2);  
  #endif        
};
//===========================================================================================================================================================

void setup()
{
  Serial.begin(SERIAL_BAUD);
  //Wire.begin(I2C_SLAVE); // join i2c bus (address optional for master)
  Wire.begin(8);
  Wire.onReceive(receiveEvent); // register event

  Set_pin_out();
  delay(200); // some time to settle

};

void loop()
{
    //delay(50);
};
