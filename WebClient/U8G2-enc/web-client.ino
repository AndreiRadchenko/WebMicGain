/*
  Web client

 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen

 */

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
//byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte mac[] = { 0x11, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 };

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
//char server[] = "www.google.com";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
//IPAddress ip(192, 168, 0, 177);
//IPAddress myDns(192, 168, 0, 1);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):

//EthernetClient client;
int client_connect;

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement

unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 15*1000;  // delay between updates, in milliseconds
IPAddress server(eeprom_config.ser_ip[0],eeprom_config.ser_ip[1],eeprom_config.ser_ip[2],eeprom_config.ser_ip[3]);

void setupNetwork() {

  // start the Ethernet connection:
  read_EEPROM_Settings();
  IPAddress server_ip(eeprom_config.ser_ip[0],eeprom_config.ser_ip[1],eeprom_config.ser_ip[2],eeprom_config.ser_ip[3]);
  server = server_ip;
  //IPAddress server(74,125,232,128);
  //Ethernet.init(10);  // Most Arduino shields

 // byte mac[] = { eeprom_config.mac[0], eeprom_config.mac[1], eeprom_config.mac[2], eeprom_config.mac[3], eeprom_config.mac[4], eeprom_config.mac[5] };  
  
 
  IPAddress ip(eeprom_config.dev_ip[0], eeprom_config.dev_ip[1], eeprom_config.dev_ip[2], eeprom_config.dev_ip[3]);                                               
  IPAddress gateway (eeprom_config.gateway[0],eeprom_config.gateway[1],eeprom_config.gateway[2],eeprom_config.gateway[3]);                      
  IPAddress subnet  (eeprom_config.subnet[0], eeprom_config.subnet[1], eeprom_config.subnet[2], eeprom_config.subnet[3]);  
  IPAddress dns_server  (eeprom_config.dns_server[0], eeprom_config.dns_server[1], eeprom_config.dns_server[2], eeprom_config.dns_server[3]);
  
  Ethernet.begin(mac, ip, dns_server);//, gateway, subnet);
  

  // give the Ethernet shield a second to initialize:
  delay(2000);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");

};

// this method makes a HTTP connection to the server:
void ccuGetParamHttpRequest(int n) {
  
  char* num;
  char buf[20];
  char ccu_name[8] = "ccu";

  num = itoa(n+1,buf,10);
  strcat(ccu_name, num);
  String PostData = ccu_name;// + "=" + ccu_name;
  PostData = PostData + "=" + PostData;
  #ifdef DEBUG
    Serial.print("PostData: ");
    Serial.println(PostData);
  #endif

  byteCount = 0;
  //String PostData = "ccu02=ccu02";
    // if you get a connection, report back via serial:
    
  if (client.connect(server, 80)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
      // Make a HTTP request:
    Serial.println("making POST request");  
    client.println("POST /ccuGetParam HTTP/1.1 ");
    //client.println("POST / / ccuGetParam");
    //client.println("Host: 192.168.32.111");
    client.println("Connection: close");
    client.println("Content-Type: text-plain");
    client.print("Content-Length: ");
    client.println(PostData.length());
    client.println();
    client.println(PostData);
    
    //client.println("Connection: keep-alive");
    //client.println("Connection: close");
    //client.println(); 
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
    delay(250); 
    beginMicros = micros();
  
  // if there are incoming bytes available
  // from the server, read them and print them:
  
  int len = client.available();
  if (len > 0) {
    byte buffer[80];
    if (len > 80) len = 80;
    client.read(buffer, len);
    if (printWebData) {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }
    byteCount = byteCount + len;

    // parse recived data ========================================================================
    String myStr((char*)buffer); 
    int delim1 = myStr.indexOf(' ');
    int delim2 = myStr.indexOf(' ', delim1+1);
    String ccuName = myStr.substring(0, delim1);
    int gaineCh1 = myStr.substring(delim1+1, delim2).toInt();
    int gaineCh2 = myStr.substring(delim2+1).toInt();
    ch1 = gaineCh1;
    ch2 = gaineCh2;
    /* Serial.println();
    Serial.print("Parsed parameter: ");
    Serial.print("ccuName = ");
    Serial.print(ccuName);
    Serial.print(", gaineCh1 = ");
    Serial.print(gaineCh1);
    Serial.print(", gaineCh2 = ");
    Serial.println(gaineCh2); */
  }
  client.stop();
    //delay(2000); 
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    endMicros = micros();
    Serial.println();
    Serial.println("disconnecting.");
    //client.stop();
    Serial.print("Received ");
    Serial.print(byteCount);
    Serial.print(" bytes in ");
    float seconds = (float)(endMicros - beginMicros) / 1000000.0;
    Serial.print(seconds, 4);
    float rate = (float)byteCount / seconds / 1000.0;
    Serial.print(", rate = ");
    Serial.print(rate);
    Serial.print(" kbytes/second");
    Serial.println();
   }
}

// this method makes a HTTP connection to the server:
void setGainHttpRequest(int ch_num, int ch_gain) {
  
  char* num;
  char buf[20];
  String PostData;

  PostData = "s";
  num = "";
  num = itoa(ccu,buf,10);
  //strcat(ch_number, num);
  PostData = PostData + String(num);
  num = "";
  num = itoa(ch_num,buf,10);
  PostData = PostData + String(num) + "=";
  num = "";
  num = itoa(ch_gain,buf,10);
  PostData = PostData + String(num);

  #ifdef DEBUG
    Serial.print("PostData: ");
    Serial.println(PostData);
  #endif

  byteCount = 0;
  //String PostData = "ccu02=ccu02";
    // if you get a connection, report back via serial:
    
  if (client.connect(server, 80)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
      // Make a HTTP request:
    Serial.println("making POST request");  
    client.println("POST /form HTTP/1.1 ");
    //client.println("POST / / ccuGetParam");
    //client.println("Host: 192.168.32.111");
    client.println("Connection: close");
    client.println("Content-Type: text-plain");
    client.print("Content-Length: ");
    client.println(PostData.length());
    client.println();
    client.println(PostData);
    
    //client.println("Connection: keep-alive");
    //client.println("Connection: close");
    //client.println(); 
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }

  client.stop();
  
}