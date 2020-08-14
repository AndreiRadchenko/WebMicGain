#include <Arduino.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"
/********************
Arduino generic menu system
U8G2 menu example
U8G2: https://github.com/olikraus/u8g2

Oct. 2016 Stephen Denne https://github.com/datacute
Based on example from Rui Azevedo - ruihfazevedo(@rrob@)gmail.com
Original from: https://github.com/christophepersoz

menu on U8G2 device
output: Wemos D1 mini OLED Shield (SSD1306 64x48 I2C) + Serial
input: Serial + encoder
mcu: nano328p

*/

#include <menu.h>
#include <menuIO/u8g2Out.h>
#include <menuIO/encoderIn.h>
#include <menuIO/keyIn.h>
#include <menuIO/chainStream.h>
#include <menuIO/serialOut.h>
#include <menuIO/serialIn.h>

using namespace Menu;

struct config_mic
{
byte mic_config_set;
unsigned char ccu_ch[32]; // global array for saving gain value
char ccu_name[16][16];    //string array for ccu names. names length is 16 char
} cfg;

#define LEDPIN LED_BUILTIN
#define __AVR_ATmega2560__

// #define USE_PCD8544
#define USE_SSD1306

#if defined(USE_SSD1306)
  // rotary encoder pins
   #define encA    62
   #define encB    63
   #define encBtn  61

  #include <Wire.h>
  //#define fontName u8g2_font_7x13_mf
  #define fontName u8g2_font_t0_17b_mf
  //#define fontX 7
  //#define fontY 16
  #define fontX 7
  #define fontY 20
  #define offsetX 0
  #define offsetY -4
  #define U8_Width 128
  #define U8_Height 64
  #define USE_HWI2C
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);//, SCL, SDA);
  // U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, U8X8_PIN_NONE, 4, 5);
  // U8G2_SSD1306_128X64_VCOMH0_F_HW_I2C u8g2(U8G2_R2, U8X8_PIN_NONE, 4, 5);
  // U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 4, 5);
#else
  #error DEFINE YOUR OUTPUT HERE.
#endif
/*
uint16_t serEther1=0;
uint16_t serEther2=0;
//uint16_t sec=0;
uint16_t serEther3=0;
uint16_t serEther4=0;

uint16_t devEther1=0;
uint16_t devEther2=0;
//uint16_t sec=0;
uint16_t devEther3=0;
uint16_t devEther4=0;
*/
struct config_t
{
    byte config_set;
    byte use_dhcp;
    byte dhcp_refresh_minutes;
    byte mac[6];
    byte ser_ip[4];
    byte dev_ip[4];
    byte gateway[4];
    byte subnet[4];
    byte dns_server[4];
    unsigned int webserverPort;
} eeprom_config;

/** 
* set_mic_default() function
*
* The default settings. 
* This settings are used when no config is present.
*/
void set_mic_default()
{
  int i, j;
  char buf[20];
  char* num; 
  
  cfg.mic_config_set = 1; // dont change! It's used to check if the config is already set
  
  for (j = 0; j <= 15; j++)
  {
    strcpy(cfg.ccu_name[j], "CCU");
    num = itoa(j+1,buf,10);
    strcat(cfg.ccu_name[j], num);
  }; 
  // global unsigned char ccu_ch[32];
  for (i = 0; i <= 31; i++)
  {
    cfg.ccu_ch[i] = 2; //-40dB потом инициализация будет значениями из EEPROM
  };
}

// define menu colors --------------------------------------------------------
//each color is in the format:
//  {{disabled normal,disabled selected},{enabled normal,enabled selected, enabled editing}}
// this is a monochromatic color table
/*
const colorDef<uint8_t> colors[6] MEMMODE={
  {{0,0},{0,1,1}},//bgColor
  {{1,1},{1,0,0}},//fgColor
  {{1,1},{1,0,0}},//valColor
  {{1,1},{1,0,0}},//unitColor
  {{0,1},{0,0,1}},//cursorColor
  {{1,1},{1,0,0}},//titleColor
};
*/
const colorDef<uint8_t> colors[6] MEMMODE={
  {{0,0},{0,1,1}},//bgColor
  {{1,1},{1,0,0}},//fgColor
  {{1,1},{1,0,0}},//valColor
  {{1,1},{1,0,0}},//unitColor
  {{0,1},{0,0,1}},//cursorColor
  {{0,1},{1,0,0}},//titleColor
};

result doAlert(eventMask e, prompt &item);

int test=55;

int ledCtrl=HIGH;

result myLedOn() {
  ledCtrl=HIGH;
  return proceed;
}
result myLedOff() {
  ledCtrl=LOW;
  return proceed;
}

result saveServerAddr(eventMask e,navNode& nav,prompt& item)
{

  switch(e) {
    case enterEvent://entering navigation level (this menu is now active)
      Serial.println(" enterEvent");
      nav.root->showTitle = true;
      break;
    case exitEvent://leaving navigation level
      Serial.println(" exitEvent");
      nav.root->showTitle = false;

      Serial.println();
      Serial.print("Server IPv4 address: ");
      Serial.print(eeprom_config.ser_ip[0]);
      Serial.print(": ");
      Serial.print(eeprom_config.ser_ip[1]);
      Serial.print(": ");
      Serial.print(eeprom_config.ser_ip[2]);
      Serial.print(": ");
      Serial.println(eeprom_config.ser_ip[3]);
      EEPROM_writeAnything(0, eeprom_config);
      break;
  }

  return proceed;
}

result saveDeviceAddr(eventMask e,navNode& nav,prompt& item)
{

  switch(e) {
    case enterEvent://entering navigation level (this menu is now active)
      Serial.println(" enterEvent");
      nav.root->showTitle = true;
      break;
    case exitEvent://leaving navigation level
      Serial.println(" exitEvent");
      nav.root->showTitle = false;

      Serial.println();
      Serial.print("Device IPv4 address: ");
      Serial.print(eeprom_config.dev_ip[0]);
      Serial.print(": ");
      Serial.print(eeprom_config.dev_ip[1]);
      Serial.print(": ");
      Serial.print(eeprom_config.dev_ip[2]);
      Serial.print(": ");
      Serial.println(eeprom_config.dev_ip[3]);
      EEPROM_writeAnything(0, eeprom_config);
      break;
  }

  return proceed;
}

TOGGLE(ledCtrl,setLed,"Led: ",doNothing,noEvent,noStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",HIGH,doNothing,noEvent)
  ,VALUE("Off",LOW,doNothing,noEvent)
);

int ccu=1;
SELECT(ccu,selCCU," CCU ",doNothing,noEvent,noStyle
  ,VALUE("CAM1",1,doNothing,noEvent)
  ,VALUE("CAM2",2,doNothing,noEvent)
  ,VALUE("CAM3",3,doNothing,noEvent)
  ,VALUE("CAM4",4,doNothing,noEvent)
  ,VALUE("CAM5",5,doNothing,noEvent)
  ,VALUE("CAM6",6,doNothing,noEvent)
  ,VALUE("CAM7",7,doNothing,noEvent)
  ,VALUE("CAM8",8,doNothing,noEvent)
  ,VALUE("CAM9",9,doNothing,noEvent)
  ,VALUE("CAM10",10,doNothing,noEvent)  
  ,VALUE("CAM11",11,doNothing,noEvent)
  ,VALUE("CAM12",12,doNothing,noEvent)
  ,VALUE("CAM13",13,doNothing,noEvent)
  ,VALUE("CAM14",14,doNothing,noEvent)
  ,VALUE("CAM15",15,doNothing,noEvent)
  ,VALUE("CAM16",16,doNothing,noEvent)  
);

int ch1=1;
SELECT(ch1,selCH1," CH1 ",doNothing,noEvent,noStyle
  ,VALUE("-20 dB",0,doNothing,noEvent)
  ,VALUE("-30 dB",1,doNothing,noEvent)
  ,VALUE("-40 dB",2,doNothing,noEvent)
  ,VALUE("-50 dB",3,doNothing,noEvent)
  ,VALUE("-60 dB",4,doNothing,noEvent)
);

int ch2=3;
SELECT(ch2,selCH2," CH2 ",doNothing,noEvent,noStyle
  ,VALUE("-20 dB",0,doNothing,noEvent)
  ,VALUE("-30 dB",1,doNothing,noEvent)
  ,VALUE("-40 dB",2,doNothing,noEvent)
  ,VALUE("-50 dB",3,doNothing,noEvent)
  ,VALUE("-60 dB",4,doNothing,noEvent)
);

int chooseTest=-1;
CHOOSE(chooseTest,chooseMenu,"Choose",doNothing,noEvent,noStyle
  ,VALUE("First",1,doNothing,noEvent)
  ,VALUE("Second",2,doNothing,noEvent)
  ,VALUE("Third",3,doNothing,noEvent)
  ,VALUE("Last",-1,doNothing,noEvent)
);

MENU(setSvrEthMenu,"Server Address",saveServerAddr,exitEvent | enterEvent,noStyle
  //,OP("Srv IPv4 addr",doNothing,noEvent)
  ,FIELD(eeprom_config.ser_ip[0],"Eth1","",0,255,10,1,doNothing,noEvent,noStyle)
  ,FIELD(eeprom_config.ser_ip[1],"Eth2","",0,255,10,1,doNothing,noEvent,noStyle)
  ,FIELD(eeprom_config.ser_ip[2],"Eth3","",0,255,10,1,doNothing,noEvent,noStyle)
  ,FIELD(eeprom_config.ser_ip[3],"Eth4","",0,255,10,1,doNothing,noEvent,noStyle)
  // ,altOP(altPrompt,"",doNothing,noEvent)
  ,EXIT("<Save")
);

MENU(setDevEthMenu,"Device Address",saveDeviceAddr,exitEvent | enterEvent,noStyle
  //,OP("Srv IPv4 addr",doNothing,noEvent)
  ,FIELD(eeprom_config.dev_ip[0],"Eth1","",0,255,10,1,doNothing,noEvent,noStyle)
  ,FIELD(eeprom_config.dev_ip[1],"Eth2","",0,255,10,1,doNothing,noEvent,noStyle)
  ,FIELD(eeprom_config.dev_ip[2],"Eth3","",0,255,10,1,doNothing,noEvent,noStyle)
  ,FIELD(eeprom_config.dev_ip[3],"Eth4","",0,255,10,1,doNothing,noEvent,noStyle)
  // ,altOP(altPrompt,"",doNothing,noEvent)
  ,EXIT("<Save")
);

MENU(ctrlMenu,"Mic Control",doNothing,noEvent,wrapStyle
  ,SUBMENU(selCCU)
  ,SUBMENU(selCH1)
  ,SUBMENU(selCH2)
);

char* constMEM hexDigit MEMMODE="0123456789ABCDEF";
char* constMEM hexNr[] MEMMODE={"0","x",hexDigit,hexDigit};
char buf1[]="0x11";

MENU(mainMenu,"",doNothing,noEvent,wrapStyle
  ,SUBMENU(ctrlMenu)
  ,SUBMENU(setSvrEthMenu)
  ,SUBMENU(setDevEthMenu)
);

// MENU(mainMenu,"",doNothing,noEvent,wrapStyle
 // ,SUBMENU(selCCU)
 // ,SUBMENU(selCH1)
 // ,SUBMENU(selCH2)
  /*
  ,OP("CCU2",doNothing,noEvent)
  ,SUBMENU(selCH1)
  ,SUBMENU(selCH2)
  /*
  ,OP("CCU3",doNothing,noEvent)
  ,SUBMENU(selCH1)
  ,SUBMENU(selCH2)
  ,OP("CCU4",doNothing,noEvent)
  ,SUBMENU(selCH1)
  ,SUBMENU(selCH2)
  */
  //,FIELD(test,"Test","%",0,100,10,1,doNothing,noEvent,wrapStyle)
  /*
  ,SUBMENU(timeMenu)
  ,SUBMENU(subMenu)
  ,SUBMENU(setLed)
  ,OP("LED On",myLedOn,enterEvent)
  ,OP("LED Off",myLedOff,enterEvent)
  ,SUBMENU(selMenu)
  ,SUBMENU(chooseMenu)
  ,OP("Alert test",doAlert,enterEvent)
  ,EDIT("Hex",buf1,hexNr,doNothing,noEvent,noStyle)
  ,EXIT("<Exit")
  */
// );

#define MAX_DEPTH 3

 encoderIn<encA,encB> encoder;//simple quad encoder driver
 encoderInStream<encA,encB> encStream(encoder,4);// simple quad encoder fake Stream

//a keyboard with only one key as the encoder button
 keyMap encBtn_map[]={{-encBtn,defaultNavCodes[enterCmd].ch}};//negative pin numbers use internal pull-up, this is on when low
 keyIn<1> encButton(encBtn_map);//1 is the number of keys

//menuIn* inputsList[]={&encButton,&Serial};
//chainStream<2> in(inputsList);//1 is the number of inputs

serialIn serial(Serial);
//MENU_INPUTS(in,&serial);
MENU_INPUTS(in,&encStream,&encButton);//,&serial);

MENU_OUTPUTS(out,MAX_DEPTH
  ,U8G2_OUT(u8g2,colors,fontX,fontY,offsetX,offsetY,{0,0,U8_Width/fontX,U8_Height/fontY})
  ,NONE
  //,SERIAL_OUT(Serial)
);

NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);

result alert(menuOut& o,idleEvent e) {
  if (e==idling) {
    o.setCursor(0,0);
    o.print("alert test");
    o.setCursor(0,1);
    o.print("press [select]");
    o.setCursor(0,2);
    o.print("to continue...");
  }
  return proceed;
}

result doAlert(eventMask e, prompt &item) {
  nav.idleOn(alert);
  return proceed;
}

//when menu is suspended
result idle(menuOut& o,idleEvent e) {
  o.clear();
  switch(e) {
    case idleStart:o.println("suspending menu!");break;
    case idling:o.println("suspended...");break;
    case idleEnd:o.println("resuming menu.");break;
  }
  return proceed;
}

void setup() {

  set_mic_default();
  read_EEPROM_Settings();

  Serial.begin(115200);
  while(!Serial);
  Serial.println("menu 4.x test");Serial.flush();
   encButton.begin();
   encoder.begin();
   pinMode(LEDPIN,OUTPUT);//cant use pin 13 when using hw spi
  // and on esp12 i2c can be on pin 2, and that is also led pin
  // so check first if this is adequate for your board
  #if defined(USE_HWSPI)
    SPI.begin();
    u8g2.begin();
  #elif defined(USE_HWI2C)
    Wire.begin();
    u8g2.begin();
  #else
    #error "please choose your interface (I2c,SPI)"
  #endif
  u8g2.setFont(fontName);
  // u8g2.setBitmapMode(0);

  // disable second option
  //mainMenu[1].enabled=disabledStatus;
  nav.idleTask=idle;//point a function to be used when menu is suspended
  nav.showTitle = false;
  Serial.println("setup done.");Serial.flush();
  //nav.doNav(navCmd(idxCmd,0)); //hilite first option
  nav.doNav(navCmd(enterCmd)); //execute option
}

void loop() {
  nav.doInput();
   digitalWrite(LEDPIN, ledCtrl);
  if (nav.changed(0)) {//only draw if menu changed for gfx device
    //change checking leaves more time for other tasks
    u8g2.firstPage();
    do nav.doOutput(); while(u8g2.nextPage());
  }
  delay(100);//simulate other tasks delay
}
