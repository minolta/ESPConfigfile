#include "Configfile.h"

Configfile::Configfile()
{
    filename = "/config.cfg";
}
Configfile::Configfile(String c)
{
    filename = c;
}

boolean Configfile::haveAlreadyConfig()
{
    return haveconfig;
}
int Configfile::configsize(void)
{
    return doc.size();
}
/**
 * ถ้า return true แสดงว่ามี file อยู่แล้ว
 * ถ้า return false แสดงว่าไม่มี file อยู่เป็นการสร้าง config ใหม่
 * **/
boolean Configfile::openFile(void)
{
#if defined(ESP32)
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        open = false;
        return open;
        // return;
    }
    else
    {
        open = true;
    }
#else
    if (!SPIFFS.begin())
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        open = false;
        return open;
        // return;
    }
    else
    {
        open = true;
    }
#endif

    if (SPIFFS.exists(filename.c_str()))
    {
        Serial.printf("Have file : %s", filename.c_str());
        haveconfig = true;
        return true;
    }
    else
    {
        //เปิด file ใหม่
        configfile = SPIFFS.open(filename.c_str(), "w");
        configfile.printf("%s\n", "new file");
        configfile.close();
        haveconfig = false;
        return false;
    }
}
String Configfile::getfilename(void)
{
    return filename;
}
void Configfile::addConfig(String valuename, String value)
{
    doc.clear();
    if (haveconfig)
        loadConfig();
    doc[valuename] = value;
    saveConfig();
}
void Configfile::addConfig(String valuename, int value)
{
    doc.clear();
    if (haveconfig)
        loadConfig();
    doc[valuename] = value;
    saveConfig();
}
void Configfile::addConfig(String valuename, long value)
{
    doc.clear();
    if (haveconfig)
        loadConfig();
    doc[valuename] = value;
    saveConfig();
}
void Configfile::addConfig(String valuename, double value)
{
    doc.clear();
    if (haveconfig)
        loadConfig();
    doc[valuename] = value;
    saveConfig();
}
DynamicJsonDocument Configfile::getAll()
{
    doc.clear();
    loadConfig();
    return doc;
}
String Configfile::getConfig(String valuename)
{
    loadConfig();
    return doc[valuename];
}
int Configfile::getIntConfig(String valuename)
{
    loadConfig();
    String t = doc[valuename];
    if (t)
    {
        return t.toInt();
    }

    return NULL;
}
double Configfile::getDobuleConfig(String valuename)
{
    loadConfig();
    String t = doc[valuename];
    return t.toDouble();
}
double Configfile::getDobuleConfig(String valuename, String defaultvalue)
{
    loadConfig();
    String t = doc[valuename];
    double p = t.toDouble();
    if (p == 0.00)
        return defaultvalue.toDouble();
    return p;
}
String Configfile::getConfig(String valuename, String defaultvalue)
{
    loadConfig();
    if (!doc.containsKey(valuename))
        return defaultvalue;
    return doc[valuename];
    // Serial.printf("\n getdefault : %d %s\n", value, value);
    // if (value.equals("null"))
    // {
    // return defaultvalue;
    // }
    // return value;
}
void Configfile::saveConfig()
{
    File file = SPIFFS.open(filename.c_str(), "w");
    char buf[CONFIGFILE_buffersize];
    serializeJsonPretty(doc, buf, CONFIGFILE_buffersize);
    file.printf("%s\n", buf);
    file.close();
}
int Configfile::loadConfig()
{
    doc.clear();
    if (SPIFFS.exists(filename.c_str()))
    {
        File file = SPIFFS.open(filename.c_str(), "r");
        String b = "";
        while (file.available())
        {
            b = b + String(file.readStringUntil('\n'));
        }
        file.close();
        deserializeJson(doc, b.c_str(), CONFIGFILE_buffersize);
        return 1;
    }
    else
    {
        return 0;
    }
}