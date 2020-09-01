
/** 
* set_EEPROM_Default() function
*
* The default settings. 
* This settings are used when no config is present or the reset button is pressed.
*/
void set_EEPROM_Default() {
    eeprom_config.config_set=1;  // dont change! It's used to check if the config is already set
  
    eeprom_config.use_dhcp=0; // use DHCP per default
    eeprom_config.dhcp_refresh_minutes=60; // refresh the DHCP every 60 minutes
  
    // set the default MAC address. In this case its DE:AD:BE:EF:FE:ED
    eeprom_config.mac[0]=0x11;  
    eeprom_config.mac[1]=0xAD;
    eeprom_config.mac[2]=0xBE;
    eeprom_config.mac[3]=0xEF;
    eeprom_config.mac[4]=0xFE;
    eeprom_config.mac[5]=0x11;
    
    // set the default IP address for server.
    eeprom_config.ser_ip[0]=192;
    eeprom_config.ser_ip[1]=168;
    eeprom_config.ser_ip[2]=32;
    eeprom_config.ser_ip[3]=111;

    // set the default IP address for the device.
    eeprom_config.dev_ip[0]=192;
    eeprom_config.dev_ip[1]=168;
    eeprom_config.dev_ip[2]=32;
    eeprom_config.dev_ip[3]=112;
  
    // set the default GATEWAY. In this case its 192.168.0.254
    eeprom_config.gateway[0]=192;
    eeprom_config.gateway[1]=168;
    eeprom_config.gateway[2]=32;
    eeprom_config.gateway[3]=254;
    
    // set the default SUBNET. In this case its 255.255.255.0
    eeprom_config.subnet[0]=255;
    eeprom_config.subnet[1]=255;
    eeprom_config.subnet[2]=255;
    eeprom_config.subnet[3]=0;

    // set the default DNS SERVER. In this case its 192.168.0.254
    eeprom_config.dns_server[0]=192;
    eeprom_config.dns_server[1]=168;
    eeprom_config.dns_server[2]=32;
    eeprom_config.dns_server[3]=254;

    // set the default Webserver Port. In this case its Port 80
    eeprom_config.webserverPort=80;
    
    #ifdef DEBUG
      Serial.println("Config reset");
    #endif 
}

void read_EEPROM_Settings() {

  
  // read the current config
  EEPROM_readAnything(0, eeprom_config);
  
  // check if config is present or if reset button is pressed
  if (eeprom_config.config_set != 1) 
  {
    // set default values
    set_EEPROM_Default();
    
    // write the config to eeprom
    EEPROM_writeAnything(0, eeprom_config);
  } 
}