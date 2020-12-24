#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#define buffersize 2048
class Configfile
{
private:
    boolean open = true;
    File configfile;
    StaticJsonDocument<buffersize> doc;
    boolean haveconfig = true;

public:
    Configfile();
    void saveConfig();
    void loadConfig();
    String getConfig(String);
    void addConfig(String, String);
    //สำหรับอ่าน config
    String readConfig(String);
    //สำหรับเขียน config
    boolean setConfig(String, String);
    boolean haveAreadyConfig();
    
};

#endif
