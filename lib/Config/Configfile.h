#ifndef CONFIGFILE_H
#define CONFIGFILE_H
#include <Arduino.h>
#if defined(ESP32)
// #include <SPIFFS.h>
#include <LITTLEFS.h>
#include "FS.h"

#else
#include "FS.h"
#endif
#include <ArduinoJson.h>
#define CONFIGFILE_buffersize 2048
class Configfile
{
private:
  boolean open = true;
  File configfile;
  boolean haveconfig = false;
  String filename;

public:
  Configfile();
  Configfile(String);
  boolean openFile(void);
  void saveConfig();
  void saveConfig(DynamicJsonDocument d);
  // int loadConfig();
  String getConfig(String);
  String getConfig(String, String);
  int getIntConfig(String, String);
  int getIntConfig(String, int);
  int getIntConfig(String);
  double getDobuleConfig(String);
  double getDobuleConfig(String, String);
  double getDobuleConfig(String, double);
  void addConfig(String, String);
  void addConfig(String, int);
  void addConfig(String, double);
  void addConfig(String, long);
  void resettodefault(void);
  DynamicJsonDocument load();
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
