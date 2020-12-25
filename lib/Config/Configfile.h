#ifndef CONFIGFILE_H
#define CONFIGFILE_H
#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#define CONFIGFILE_buffersize 2048
class Configfile
{
private:
    boolean open = true;
    File configfile;
    StaticJsonDocument<CONFIGFILE_buffersize> doc;
    boolean haveconfig = false;
    String filename;

public:
    Configfile();
    Configfile(String);
    boolean openFile(void);
    void saveConfig();
    int loadConfig();
    String getConfig(String);
    void addConfig(String, String);
    //สำหรับอ่าน config
    String readConfig(String);
    //สำหรับเขียน config
    boolean setConfig(String, String);
    boolean haveAlreadyConfig();
    String getfilename(void);
    int configsize(void);
    DynamicJsonDocument getAll(void);
};

#endif
