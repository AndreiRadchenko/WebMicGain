#include "MicRemote.h"
#include "stdio.h"
#include "stdlib.h"
#include "MyNetSetup.h"
//#include "pcint.h"

#define EEPROM_ETHER 0
#define EEPROM_SET 50
#define EEPROM_CCU_CH 60
#define EEPROM_CCU_NAME 100

// Power-Down Add-On Hardware
//const byte interruptPin = 69; //D19

// no-cost stream operator as described at 
// http://sundial.org/arduino/?page_id=119
template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }


// CHANGE THIS TO YOUR OWN UNIQUE VALUE
//static uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0x11, 0xFE, 0xED };

// CHANGE THIS TO MATCH YOUR HOST NETWORK
//static uint8_t ip[] = { 192, 168, 32, 111 };

#define PREFIX ""
//WebServer webserver(PREFIX, 80);

/* This creates an pointer to instance of the webserver. */
WebServer * webserver;

struct config_mic
{
byte mic_config_set;
unsigned char ccu_ch[32]; // global array for saving gain value
char ccu_name[16][16];    //string array for ccu names. names length is 16 char
} cfg;

//byte mic_config_set;
//unsigned char ccu_ch[24]; // global array for saving gain value
//char ccu_name[12][16];    //string array for ccu names. names length is 16 char
char ccu;
char mic1;
char mic2;

//move web page code to programm memory
//P(Http400) = "HTTP 400 - BAD REQUEST";
//server.printP(table_tr_end);
/*
P(br) = "<br>\n";
P(table_start) = "<table>";
P(table_tr_start) = "<tr>";
P(table_tr_end) = "</tr>";
P(table_td_start) = "<td>";
P(table_td_end) = "</td>";
P(table_end) = "</table>"; 
*/
P(ccu_table_td_start) = "<td> <p align=right> <input type='text' style='background-color:Khaki;'";
P(ccu_table_td_end) = "</select> </p> </td>";
P(ccu_ch1) = "<br> </p> <p> CH1 <select name='";
P(ccu_ch2) = "</select> </p> <p> CH2 <select name='";

// commands are functions that get called by the webserver framework
// they can read any posted data from client, and they output to server

void outputPins(WebServer &server, WebServer::ConnectionType type, bool addControls = false)
{
  #ifdef DEBUG    
      Serial.println("Respons to GET request...");   
  #endif     
  P(htmlHead) =
    "<html>"
    "<head>"
    "<title>Mic control</title>"
    "<meta http-equiv='Content-Type' content='text/html; charset=windows-1251'>"
    "<meta name='Keywords' content='Mic control'>"
    
    "<script type=\"text/javascript\">"
    "function send_param(ccu_ch, index)" 
     "{"
        "var body = ccu_ch + '=' + index;"
        "xhr.open('POST', '" PREFIX "/form', true);"
        "xhr.setRequestHeader('Content-Type', 'text-plain');"
        "xhr.send(body);"                
     "}" 
     
     "function send_name(ccu_namber, ccu_name)" 
     "{"
        "var body = ccu_namber + '=' + ccu_name;"
        "xhr.open('POST', '" PREFIX "/ccuName', true);"
        "xhr.setRequestHeader('Content-Type', 'text-plain');"
        "xhr.send(body);"                
     "}"
     
     "function save_param()" 
     "{"
        "var body = 'eeprom' + '=' + '50';"       
        "xhr.open('POST', '" PREFIX "/saveParam', true);"
        "xhr.setRequestHeader('Content-Type', 'text-plain');"
        "xhr.send(body);" 
        "window.alert('Mic Settings are Saved');"        
     "}"

     "function set_param()" 
     "{"
        "var body = 'param' + '=' + 'set';"       
        "xhr.open('POST', '" PREFIX "/setParam', true);"
        "xhr.setRequestHeader('Content-Type', 'text-plain');"
        "xhr.send(body);"
        "window.alert('Microphones level being setted\\. It\\'s take 5 seconds\\..');"  
        //"window.alert('Mic's level being setted. It's take 5 seconds');"        
     "}"
     
    "</script>"   
    
    "</head>"
    "<body>";

  server.httpSuccess();
  server.printP(htmlHead);
  
  int i;                //may be it is needless variable
  int j;
  int k;
  char ccu_ch_name[4];

    server << "<h1>Sony cameras remout mic control</h1>";
    server << "<table border='1' bgcolor='white' bordercolor='black' cellpadding='10'>";
    server << "<tr>";
    server << "<form action='' method='POST' name='form1'>";

    //"CCU1"
    server.printP(ccu_table_td_start);
    server << "name='ccu01' maxlength='11' size='11' value='" << cfg.ccu_name[0] << "' onchange=\"send_name('ccu01', document.form1.ccu01.value)\">";
        server.printP(ccu_ch1);    
        server <<"s011"<< "' onchange=\"send_param('s011', document.form1.s011.selectedIndex)\">"; 
        selectedOptions(server, cfg.ccu_ch[0]);  //output select list with previous selected options 
        server.printP(ccu_ch2);
        server <<"s012"<< "' onchange=\"send_param('s012', document.form1.s012.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[1]);          
       	//server << "</select> </p>"; 
    server.printP(ccu_table_td_end);
   
   //"CCU2"
   server.printP(ccu_table_td_start);
   server << "name='ccu02' maxlength='11' size='11' value='" << cfg.ccu_name[1] << "' onchange=\"send_name('ccu02', document.form1.ccu02.value)\">";
        server.printP(ccu_ch1);
        server <<"s021"<< "' onchange=\"send_param('s021', document.form1.s021.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[2]);        
        server.printP(ccu_ch2);
        server <<"s022"<< "' onchange=\"send_param('s022', document.form1.s022.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[3]);        
       	//server << "</select> </p>";
   server.printP(ccu_table_td_end);    
   
   //"CCU3"
   server.printP(ccu_table_td_start);
   server << "name='ccu03' maxlength='11' size='11' value='" << cfg.ccu_name[2] << "' onchange=\"send_name('ccu03', document.form1.ccu03.value)\">";
        server.printP(ccu_ch1);
        server <<"s031"<< "' onchange=\"send_param('s031', document.form1.s031.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[4]);        
        server.printP(ccu_ch2);
        server <<"s032"<< "' onchange=\"send_param('s032', document.form1.s032.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[5]);        
       	//server << "</select> </p>";
   server.printP(ccu_table_td_end);
   
   //"CCU4"
   server.printP(ccu_table_td_start);
   server << "name='ccu04' maxlength='11' size='11' value='" << cfg.ccu_name[3] << "' onchange=\"send_name('ccu04', document.form1.ccu04.value)\">";
        server.printP(ccu_ch1);
        server <<"s041"<< "' onchange=\"send_param('s041', document.form1.s041.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[6]);     
       	server << "</select> </p>";
        server << "<p>" << "CH2 ";
        server << "<select name='" <<"s042"<< "' onchange=\"send_param('s042', document.form1.s042.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[7]);        
       	//server << "</select> </p>";
   server.printP(ccu_table_td_end);
   
   //"CCU5"
   server.printP(ccu_table_td_start);
   server << "name='ccu05' maxlength='11' size='11' value='" << cfg.ccu_name[4] << "' onchange=\"send_name('ccu05', document.form1.ccu05.value)\">";
        server.printP(ccu_ch1);
        server <<"s051"<< "' onchange=\"send_param('s051', document.form1.s051.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[8]);     
       	server << "</select> </p>";
        server << "<p>" << "CH2 ";
        server << "<select name='" <<"s052"<< "' onchange=\"send_param('s052', document.form1.s052.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[9]);        
       	//server << "</select> </p>";
   server.printP(ccu_table_td_end);   
    
   //"CCU6"
   server.printP(ccu_table_td_start);
   server << "name='ccu06' maxlength='11' size='11' value='" << cfg.ccu_name[5] << "' onchange=\"send_name('ccu06', document.form1.ccu06.value)\">";
        server.printP(ccu_ch1);
        server <<"s061"<< "' onchange=\"send_param('s061', document.form1.s061.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[10]);     
       	server << "</select> </p>";
        server << "<p>" << "CH2 ";
        server << "<select name='" <<"s062"<< "' onchange=\"send_param('s062', document.form1.s062.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[11]);        
       	//server << "</select> </p>";
   server.printP(ccu_table_td_end);

   //"CCU7"
   server.printP(ccu_table_td_start);
   server << "name='ccu07' maxlength='11' size='11' value='" << cfg.ccu_name[6] << "' onchange=\"send_name('ccu07', document.form1.ccu07.value)\">";
        server.printP(ccu_ch1);
        server <<"s071"<< "' onchange=\"send_param('s071', document.form1.s071.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[12]);     
       	server << "</select> </p>";
        server << "<p>" << "CH2 ";
        server << "<select name='" <<"s072"<< "' onchange=\"send_param('s072', document.form1.s072.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[13]);        
       	//server << "</select> </p>";
   server.printP(ccu_table_td_end);
    
   //"CCU8"
   server.printP(ccu_table_td_start);
   server << "name='ccu08' maxlength='11' size='11' value='" << cfg.ccu_name[7] << "' onchange=\"send_name('ccu08', document.form1.ccu08.value)\">";
        server.printP(ccu_ch1);
        server <<"s081"<< "' onchange=\"send_param('s081', document.form1.s081.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[14]);     
       	server << "</select> </p>";
        server << "<p>" << "CH2 ";
        server << "<select name='" <<"s082"<< "' onchange=\"send_param('s082', document.form1.s082.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[15]);        
       	server << "</select> </p>";
   server << "</td> </tr> <p> <br> </p>";

   server << "<tr>";

   //"CCU9"
   server.printP(ccu_table_td_start);
   server << "name='ccu09' maxlength='11' size='11' value='" << cfg.ccu_name[8] << "' onchange=\"send_name('ccu09', document.form1.ccu09.value)\">";
        server.printP(ccu_ch1);
        server <<"s091"<< "' onchange=\"send_param('s091', document.form1.s091.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[16]);     
       	server << "</select> </p>";
        server << "<p>" << "CH2 ";
        server << "<select name='" <<"s092"<< "' onchange=\"send_param('s092', document.form1.s092.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[17]);        
       	//server << "</select> </p>";
   server.printP(ccu_table_td_end); 
    
   //"CCU10"
   server.printP(ccu_table_td_start);
   server << "name='ccu10' maxlength='11' size='11' value='" << cfg.ccu_name[9] << "' onchange=\"send_name('ccu10', document.form1.ccu10.value)\">";
        server.printP(ccu_ch1);
        server <<"s101"<< "' onchange=\"send_param('s101', document.form1.s101.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[18]);     
       	server << "</select> </p>";
        server << "<p>" << "CH2 ";
        server << "<select name='" <<"s102"<< "' onchange=\"send_param('s102', document.form1.s102.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[19]);        
       	//server << "</select> </p>";
   server.printP(ccu_table_td_end);
    
   //"CCU11"
   server.printP(ccu_table_td_start);
   server << "name='ccu11' maxlength='11' size='11' value='" << cfg.ccu_name[10] << "' onchange=\"send_name('ccu11', document.form1.ccu11.value)\">";
        server.printP(ccu_ch1);
        server <<"s111"<< "' onchange=\"send_param('s111', document.form1.s111.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[20]);     
       	server << "</select> </p>";
        server << "<p>" << "CH2 ";
        server << "<select name='" <<"s112"<< "' onchange=\"send_param('s112', document.form1.s112.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[21]);        
       	//server << "</select> </p>";
   server.printP(ccu_table_td_end);
    
   //"CCU12"
   server.printP(ccu_table_td_start);
   server << "name='ccu12' maxlength='11' size='11' value='" << cfg.ccu_name[11] << "' onchange=\"send_name('ccu12', document.form1.ccu12.value)\">";
        server.printP(ccu_ch1);
        server <<"s121"<< "' onchange=\"send_param('s121', document.form1.s121.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[22]);     
       	server << "</select> </p>";
        server << "<p>" << "CH2 ";
        server << "<select name='" <<"s122"<< "' onchange=\"send_param('s122', document.form1.s122.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[23]);        
       	//server << "</select> </p>";
   server.printP(ccu_table_td_end);

   //"CCU13"
   server.printP(ccu_table_td_start);
   server << "name='ccu13' maxlength='11' size='11' value='" << cfg.ccu_name[12] << "' onchange=\"send_name('ccu13', document.form1.ccu13.value)\">";
        server.printP(ccu_ch1);
        server <<"s131"<< "' onchange=\"send_param('s131', document.form1.s131.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[24]);     
       	server << "</select> </p>";
        server << "<p>" << "CH2 ";
        server << "<select name='" <<"s132"<< "' onchange=\"send_param('s132', document.form1.s132.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[25]);        
       	//server << "</select> </p>";
   server.printP(ccu_table_td_end);

   // <<  "CCU14"
   server.printP(ccu_table_td_start);
   server << "name='ccu14' maxlength='11' size='11' value='" << cfg.ccu_name[13] << "' onchange=\"send_name('ccu14', document.form1.ccu14.value)\">";
        server.printP(ccu_ch1);
        server <<"s141"<< "' onchange=\"send_param('s141', document.form1.s141.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[26]);     
       	server << "</select> </p>";
        server << "<p>" << "CH2 ";
        server << "<select name='" <<"s142"<< "' onchange=\"send_param('s142', document.form1.s142.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[27]);        
       	//server << "</select> </p>";
   server.printP(ccu_table_td_end);

   //"CCU15"
   server.printP(ccu_table_td_start);
   server << "name='ccu15' maxlength='11' size='11' value='" << cfg.ccu_name[14] << "' onchange=\"send_name('ccu15', document.form1.ccu15.value)\">";
        server.printP(ccu_ch1);
        server <<"s151"<< "' onchange=\"send_param('s151', document.form1.s151.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[28]);     
       	server << "</select> </p>";
        server << "<p>" << "CH2 ";
        server << "<select name='" <<"s152"<< "' onchange=\"send_param('s152', document.form1.s152.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[29]);        
       	//server << "</select> </p>";
   server.printP(ccu_table_td_end);  

   //"CCU16"
   server.printP(ccu_table_td_start);
   server << "name='ccu16' maxlength='11' size='11' value='" << cfg.ccu_name[15] << "' onchange=\"send_name('ccu16', document.form1.ccu16.value)\">";
        server.printP(ccu_ch1);
        server <<"s161"<< "' onchange=\"send_param('s161', document.form1.s161.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[30]);     
       	server << "</select> </p>";
        server << "<p>" << "CH2 ";
        server << "<select name='" <<"s162"<< "' onchange=\"send_param('s162', document.form1.s162.selectedIndex)\">";
        selectedOptions(server, cfg.ccu_ch[31]);        
       	//server << "</select> </p>";
   server.printP(ccu_table_td_end);  

  server << "</tr>";
  server << "</table>";// <p> <br> </p>";
  server << "</form>";
  server << "<p> <br> <br> <br> <input type='submit' name='button' value='Save Settings'  onClick=\"save_param()\">";// </p>"; 
  server << " <input type='submit' name='button2' value='Set All Microphones'  onClick=\"set_param()\"> </p>";
  server << "<p> <br> <br> <br> <br> <br> <br> <br> <br> <a href=\"setupNet.html\">NETWORK SETUP</a> </p>";
 
  
  server << "<script type=\"text/javascript\">";
  server << "xhr = new XMLHttpRequest();";
  server << "</script>";
  
  server << "</body></html>";

};

//output select list with previous selected options 
void selectedOptions(WebServer &server, unsigned char ccu_ch_stored)
{
          //set the previous seved value as selected option
        if (ccu_ch_stored == 0)
          server << "<option selected>- 20 dB</option>";
        else
          server << "<option>- 20 dB</option>";
          
        if (ccu_ch_stored == 1)
          server << "<option selected>- 30 dB</option>";
        else
          server << "<option>- 30 dB</option>";

        if (ccu_ch_stored == 2)
          server << "<option selected>- 40 dB</option>";
        else
          server << "<option>- 40 dB</option>";

        if (ccu_ch_stored == 3)
          server << "<option selected>- 50 dB</option>";
        else
          server << "<option>- 50 dB</option>";
          
        if (ccu_ch_stored == 4)
          server << "<option selected>- 60 dB</option>";
        else
          server << "<option>- 60 dB</option>";
};

void formCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  if (type == WebServer::POST)
  {    

    bool repeat;
    char pname[16];
    char value[16];
    int  ch_number;

    do
    {
      repeat = server.readPOSTparam(pname, 16, value, 16);
      //ch_number = atoi((pname+1));
      ch_number = (int) strtoul((pname+1), NULL, 10);

      #ifdef DEBUG
         Serial.print("formCmd() pname = ");
         Serial.print(pname);
         Serial.print(" value = ");
         Serial.println(value);
      #endif   
      
      if (repeat)
     {
      
       switch (ch_number)
          {
            case 11:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[1-1] = mic1;
                  mic2 = cfg.ccu_ch[2-1];
                  gain_change_ccu(CCU1_out, mic1, mic2);
                  break;
            case 12:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[2-1] = mic2;
                  mic1 = cfg.ccu_ch[1-1];
                  gain_change_ccu(CCU1_out, mic1, mic2);
                  break;
                  
             case 21:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[3-1] = mic1;
                  mic2 = cfg.ccu_ch[4-1];
                  gain_change_ccu(CCU2_out, mic1, mic2);
                  break;
            case 22:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[4-1] = mic2;
                  mic1 = cfg.ccu_ch[3-1];
                  gain_change_ccu(CCU2_out, mic1, mic2);
                  break;                 
                  
            case 31:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[5-1] = mic1;
                  mic2 = cfg.ccu_ch[6-1];
                  gain_change_ccu(CCU3_out, mic1, mic2);
                  break;
            case 32:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[6-1] = mic2;
                  mic1 = cfg.ccu_ch[5-1];
                  gain_change_ccu(CCU3_out, mic1, mic2);
                  break; 

             case 41:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[7-1] = mic1;
                  mic2 = cfg.ccu_ch[8-1];
                  gain_change_ccu(CCU4_out, mic1, mic2);
                  break;
            case 42:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[8-1] = mic2;
                  mic1 = cfg.ccu_ch[7-1];
                  gain_change_ccu(CCU4_out, mic1, mic2);
                  break; 
                  
             case 51:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[9-1] = mic1;
                  mic2 = cfg.ccu_ch[10-1];
                  gain_change_ccu(CCU5_out, mic1, mic2);
                  break;
            case 52:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[10-1] = mic2;
                  mic1 = cfg.ccu_ch[9-1];
                  gain_change_ccu(CCU5_out, mic1, mic2);
                  break; 

             case 61:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[11-1] = mic1;
                  mic2 = cfg.ccu_ch[12-1];
                  gain_change_ccu(CCU6_out, mic1, mic2);
                  break;
            case 62:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[12-1] = mic2;
                  mic1 = cfg.ccu_ch[11-1];
                  gain_change_ccu(CCU6_out, mic1, mic2);
                  break; 

            case 71:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[13-1] = mic1;
                  mic2 = cfg.ccu_ch[14-1];
                  gain_change_ccu(CCU7_out, mic1, mic2);
                  break;
            case 72:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[14-1] = mic2;
                  mic1 = cfg.ccu_ch[13-1];
                  gain_change_ccu(CCU7_out, mic1, mic2);
                  break;

            case 81:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[15-1] = mic1;
                  mic2 = cfg.ccu_ch[16-1];
                  gain_change_ccu(CCU8_out, mic1, mic2);
                  break;
            case 82:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[16-1] = mic2;
                  mic1 = cfg.ccu_ch[15-1];
                  gain_change_ccu(CCU8_out, mic1, mic2);
                  break;     
 
             case 91:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[17-1] = mic1;
                  mic2 = cfg.ccu_ch[18-1];
                  gain_change_ccu(CCU9_out, mic1, mic2);
                  break;
            case 92:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[18-1] = mic2;
                  mic1 = cfg.ccu_ch[17-1];
                  gain_change_ccu(CCU9_out, mic1, mic2);
                  break;     
 
            case 101:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[19-1] = mic1;
                  mic2 = cfg.ccu_ch[20-1];
                  gain_change_ccu(CCU10_out, mic1, mic2);
                  break;
            case 102:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[20-1] = mic2;
                  mic1 = cfg.ccu_ch[19-1];
                  gain_change_ccu(CCU10_out, mic1, mic2);
                  break;  

            case 111:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[21-1] = mic1;
                  mic2 = cfg.ccu_ch[22-1];
                  ccu_gain_transmit(CCU11, mic1, mic2);
//todo: define CCU11_out for i2c connected mega //gain_change_ccu(CCU11_out, mic1, mic2);
                  break;
            case 112:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[22-1] = mic2;
                  mic1 = cfg.ccu_ch[21-1];
                  ccu_gain_transmit(CCU11, mic1, mic2);
                  //gain_change_ccu(CCU11_out, mic1, mic2);
                  break; 
 
            case 121:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[23-1] = mic1;
                  mic2 = cfg.ccu_ch[24-1];
                  ccu_gain_transmit(CCU12, mic1, mic2);
//todo: define CCU12_out for i2c connected mega //gain_change_ccu(CCU12_out, mic1, mic2);
                  break;
            case 122:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[24-1] = mic2;
                  mic1 = cfg.ccu_ch[23-1];
                  ccu_gain_transmit(CCU12, mic1, mic2);
                  //gain_change_ccu(CCU12_out, mic1, mic2);
                  break;

            case 131:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[25-1] = mic1;
                  mic2 = cfg.ccu_ch[26-1];
                  ccu_gain_transmit(CCU13, mic1, mic2);
//todo: define CCU13_out for i2c connected mega //gain_change_ccu(CCU13_out, mic1, mic2);
                  break;
            case 132:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[26-1] = mic2;
                  mic1 = cfg.ccu_ch[25-1];
                  ccu_gain_transmit(CCU13, mic1, mic2);
                  //gain_change_ccu(CCU13_out, mic1, mic2);
                  break; 

            case 141:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[27-1] = mic1;
                  mic2 = cfg.ccu_ch[28-1];
                  ccu_gain_transmit(CCU14, mic1, mic2);
//todo: define CCU14_out for i2c connected mega //gain_change_ccu(CCU14_out, mic1, mic2);
                  break;
            case 142:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[28-1] = mic2;
                  mic1 = cfg.ccu_ch[27-1];
                  ccu_gain_transmit(CCU14, mic1, mic2);
                  //gain_change_ccu(CCU14_out, mic1, mic2);
                  break;

            case 151:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[29-1] = mic1;
                  mic2 = cfg.ccu_ch[30-1];
                  ccu_gain_transmit(CCU15, mic1, mic2);
//todo: define CCU15_out for i2c connected mega //gain_change_ccu(CCU15_out, mic1, mic2);
                  break;
            case 152:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[30-1] = mic2;
                  mic1 = cfg.ccu_ch[29-1];
                  ccu_gain_transmit(CCU15, mic1, mic2);
                  //gain_change_ccu(CCU15_out, mic1, mic2);
                  break;

            case 161:
                  mic1 = (char) strtoul(value, NULL, 10); //save changed value to global array ccu_ch and give from array unchaged mic value
                  cfg.ccu_ch[31-1] = mic1;
                  mic2 = cfg.ccu_ch[32-1];
                  ccu_gain_transmit(CCU16, mic1, mic2);
//todo: define CCU16_out for i2c connected mega //gain_change_ccu(CCU16_out, mic1, mic2);
                  break;
            case 162:
                  mic2 = (char) strtoul(value, NULL, 10);
                  cfg.ccu_ch[32-1] = mic2;
                  mic1 = cfg.ccu_ch[31-1];
                  ccu_gain_transmit(CCU16, mic1, mic2);
                  //gain_change_ccu(CCU16_out, mic1, mic2);
                  break;                                              
                   
            default:
                  break;
          };
        #ifdef DEBUG
          Serial.print("ch_number - ");
          Serial.println(ch_number);
          Serial.print(" mic: ");
          Serial.println(value);
        #endif

      };
    } while (repeat);
    
//    server.httpSeeOther(PREFIX "/form");
  }
  else
  ;
//    outputPins(server, type, false);
};

//===========================================================================================================================================================

void ccuNameCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  if (type == WebServer::POST)
  {    

    bool repeat;
    char pname[16];
    char value[16];
    int  ccu_number;

    do
    {
      repeat = server.readPOSTparam(pname, 16, value, 16);
      //ch_number = atoi((pname+1));
      ccu_number = (int) strtoul((pname+3), NULL, 10);      

      if (repeat)
     {
      
       switch (ccu_number)
          {
            case 1:
                  strcpy(cfg.ccu_name[0], value); //save changed ccu name to global array ccu_name[12][16] 
                  break;
            case 2:
                  strcpy(cfg.ccu_name[1], value); //save changed ccu name to global array ccu_name[12][16] 
                  break;                  
            case 3:
                  strcpy(cfg.ccu_name[2], value); //save changed ccu name to global array ccu_name[12][16] 
                  break;
            case 4:
                  strcpy(cfg.ccu_name[3], value); //save changed ccu name to global array ccu_name[12][16] 
                  break;
            case 5:
                  strcpy(cfg.ccu_name[4], value); //save changed ccu name to global array ccu_name[12][16] 
                  break;
            case 6:
                  strcpy(cfg.ccu_name[5], value); //save changed ccu name to global array ccu_name[12][16] 
                  break;
            case 7:
                  strcpy(cfg.ccu_name[6], value); //save changed ccu name to global array ccu_name[12][16] 
                  break;
            case 8:
                  strcpy(cfg.ccu_name[7], value); //save changed ccu name to global array ccu_name[12][16] 
                  break;                 
            case 9:
                  strcpy(cfg.ccu_name[8], value); //save changed ccu name to global array ccu_name[12][16] 
                  break;
            case 10:
                  strcpy(cfg.ccu_name[9], value); //save changed ccu name to global array ccu_name[12][16] 
                  break;
            case 11:
                  strcpy(cfg.ccu_name[10], value); //save changed ccu name to global array ccu_name[12][16] 
                  break;
            case 12:
                  strcpy(cfg.ccu_name[11], value); //save changed ccu name to global array ccu_name[12][16] 
                  break;
            case 13:
                  strcpy(cfg.ccu_name[12], value); //save changed ccu name to global array ccu_name[16][16] 
                  break;
            case 14:
                  strcpy(cfg.ccu_name[13], value); //save changed ccu name to global array ccu_name[16][16] 
                  break;
            case 15:
                  strcpy(cfg.ccu_name[14], value); //save changed ccu name to global array ccu_name[16][16] 
                  break;
            case 16:
                  strcpy(cfg.ccu_name[15], value); //save changed ccu name to global array ccu_name[16][16] 
                  break;                          
            default:
                  break;
          };

      };//if(repeat)
    } while (repeat);
    
//    server.httpSeeOther(PREFIX "/form");
  }
  else
  ;
//    outputPins(server, type, false);
};
//===========================================================================================================================================================

void ccuGetParamCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  if (type == WebServer::POST)
  {    

    bool repeat;
    char pname[16];
    char value[16];
    int  ccu_number;

    do
    {
      repeat = server.readPOSTparam(pname, 16, value, 16);
      //ch_number = atoi((pname+1));
      ccu_number = (int) strtoul((pname+3), NULL, 10);      
      #ifdef DEBUG    
         Serial.println("Respons to POST request..."); 
         Serial.print("pname = "); 
         Serial.println(pname); 
         Serial.print("value = ");   
         Serial.println(value);  
       #endif
      if (repeat)
     {
       #ifdef DEBUG    
         Serial.println("running ccuGetParamCmd()...");   
       #endif     
       //server.httpSuccess();
       //server << "<html><body>";
       server<<cfg.ccu_name[ccu_number-1]<<" "<<cfg.ccu_ch[2*(ccu_number-1)]<<" "<<cfg.ccu_ch[2*ccu_number-1];
       //server << "</body></html>";
      };//if(repeat)
    } while (repeat);
    
//    server.httpSeeOther(PREFIX "/form");
  }
};
//===========================================================================================================================================================


void saveParamCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{  
     EEPROM_writeAnything(EEPROM_SET, cfg);
};

/* void saveParam()
{  
     #ifdef DEBUG    
         Serial.println("Save param on turn off");   
     #endif 
     EEPROM_writeAnything(EEPROM_SET, cfg);
     PCdetachInterrupt<interruptPin>();
}; */

void setParamCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete) 
{
  gain_change_ccu(CCU1_out, cfg.ccu_ch[0], cfg.ccu_ch[1]);
  gain_change_ccu(CCU2_out, cfg.ccu_ch[2], cfg.ccu_ch[3]);
  gain_change_ccu(CCU3_out, cfg.ccu_ch[4], cfg.ccu_ch[5]);  
  gain_change_ccu(CCU4_out, cfg.ccu_ch[6], cfg.ccu_ch[7]); 
  gain_change_ccu(CCU5_out, cfg.ccu_ch[8], cfg.ccu_ch[9]); 
  gain_change_ccu(CCU6_out, cfg.ccu_ch[10], cfg.ccu_ch[11]);
  gain_change_ccu(CCU7_out, cfg.ccu_ch[12], cfg.ccu_ch[13]);
  gain_change_ccu(CCU8_out, cfg.ccu_ch[14], cfg.ccu_ch[15]);
  gain_change_ccu(CCU9_out, cfg.ccu_ch[16], cfg.ccu_ch[17]);
  gain_change_ccu(CCU10_out, cfg.ccu_ch[18], cfg.ccu_ch[19]);
  ccu_gain_transmit(CCU11, cfg.ccu_ch[20], cfg.ccu_ch[21]);
  ccu_gain_transmit(CCU12, cfg.ccu_ch[22], cfg.ccu_ch[23]);
  ccu_gain_transmit(CCU13, cfg.ccu_ch[24], cfg.ccu_ch[25]);
  ccu_gain_transmit(CCU14, cfg.ccu_ch[26], cfg.ccu_ch[27]);
  ccu_gain_transmit(CCU15, cfg.ccu_ch[28], cfg.ccu_ch[29]);
  ccu_gain_transmit(CCU16, cfg.ccu_ch[30], cfg.ccu_ch[31]);
  #ifdef DEBUG
      Serial.println("All mics are setted");
  #endif    
};

void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{  
    outputPins(server, type, false);  
};

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
  // global unsigned char ccu_ch[24];
  for (i = 0; i <= 31; i++)
  {
    cfg.ccu_ch[i] = 2; //-40dB потом инициализация будет значениями из EEPROM
  };
  #ifdef DEBUG
      Serial.println("set_mic_default()..");
  #endif 
}

/**
* read_EEPROM_Settings function
* This function is used to read the EEPROM settings at startup
*
* Overview:
* - Load the stored data from EEPROM
* - Check if a config is stored. If the conditions is ture, set the defaults
*/
void read_mic_settings() 
{ 
  // read the current config
  //Serial.println("reading mic setting");
  EEPROM_readAnything(EEPROM_SET, cfg);
  
  // check if config is present or if reset button is pressed
  if ((cfg.mic_config_set != 1) || (digitalRead(RESET_PIN) == LOW)) 
  {
    // set default values
    set_mic_default();   
    // write the config to eeprom
    EEPROM_writeAnything(EEPROM_SET, cfg);
  }
  //Serial.println("exit reading mic setting"); 
}

void setup()
{
  pinMode(RESET_PIN, INPUT);
  digitalWrite(RESET_PIN, HIGH); //5 pin pull down during startup for reset to default
  //pinMode(interruptPin, INPUT_PULLUP);

  //PCdetachInterrupt<interruptPin>();

  Serial.begin(SERIAL_BAUD);
  Wire.begin(); // join i2c bus (address optional for master)
  
  Set_pin_out();
  delay(200); // some time to settle
  // set pins for digital outputs
  read_mic_settings(); 
  
  //set_mic_default();
  
  //delay(500);
  //set out pins to saved value
  gain_change_ccu(CCU1_out, cfg.ccu_ch[0], cfg.ccu_ch[1]);
  gain_change_ccu(CCU2_out, cfg.ccu_ch[2], cfg.ccu_ch[3]);
  gain_change_ccu(CCU3_out, cfg.ccu_ch[4], cfg.ccu_ch[5]);  
  gain_change_ccu(CCU4_out, cfg.ccu_ch[6], cfg.ccu_ch[7]); 
  gain_change_ccu(CCU5_out, cfg.ccu_ch[8], cfg.ccu_ch[9]); 
  gain_change_ccu(CCU6_out, cfg.ccu_ch[10], cfg.ccu_ch[11]);
  gain_change_ccu(CCU7_out, cfg.ccu_ch[12], cfg.ccu_ch[13]);
  gain_change_ccu(CCU8_out, cfg.ccu_ch[14], cfg.ccu_ch[15]);
  gain_change_ccu(CCU9_out, cfg.ccu_ch[16], cfg.ccu_ch[17]);
  gain_change_ccu(CCU10_out, cfg.ccu_ch[18], cfg.ccu_ch[19]);
  ccu_gain_transmit(CCU11, cfg.ccu_ch[20], cfg.ccu_ch[21]);
  ccu_gain_transmit(CCU12, cfg.ccu_ch[22], cfg.ccu_ch[23]);
  ccu_gain_transmit(CCU13, cfg.ccu_ch[24], cfg.ccu_ch[25]);
  ccu_gain_transmit(CCU14, cfg.ccu_ch[26], cfg.ccu_ch[27]);
  ccu_gain_transmit(CCU15, cfg.ccu_ch[28], cfg.ccu_ch[29]);
  ccu_gain_transmit(CCU16, cfg.ccu_ch[30], cfg.ccu_ch[31]);
  //gain_change_ccu(CCU11_out, cfg.ccu_ch[20], cfg.ccu_ch[21]);
  //gain_change_ccu(CCU12_out, cfg.ccu_ch[22], cfg.ccu_ch[23]);
  
  /* initialize the Ethernet adapter with the settings from eeprom */

  setupNetwork();

  // start the Ethernet connection and the server:
  //Ethernet.begin(eeprom_config.mac, eeprom_config.ip);
  
  delay(200); // some time to settle
  webserver = new WebServer(PREFIX, eeprom_config.webserverPort);
  
  webserver->setDefaultCommand(&defaultCmd);
  webserver->addCommand("form", &formCmd);  
  webserver->addCommand("ccuName", &ccuNameCmd); 
  webserver->addCommand("saveParam", &saveParamCmd);
  webserver->addCommand("setParam", &setParamCmd);    
  webserver->addCommand("ccuGetParam", &ccuGetParamCmd);
   /* setup our default command that will be run when the user accesses
   * a page NOT on the server */
  webserver->setFailureCommand(&errorHTML);
  /* display a network setup form. The configuration is stored in eeprom */
  webserver->addCommand("setupNet.html", &setupNetHTML);

  /* start the webserver */
  webserver->begin(); 
  //delay(200); // some time to settle
  //attachInterrupt(digitalPinToInterrupt(interruptPin), saveParam, FALLING); // ISR for power down detect
  //PCattachInterrupt<interruptPin>(saveParam, FALLING);

};

void loop()
{
  // renew DHCP lease
  renewDHCP(eeprom_config.dhcp_refresh_minutes);

  char buff[200];
  int len = 200;

  /* process incoming connections one at a time forever */
  webserver->processConnection(buff, &len);
  // if you wanted to do other work based on a connecton, it would go here
};
