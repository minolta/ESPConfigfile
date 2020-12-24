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

    if (SPIFFS.exists(filename))
    {
        Serial.printf("Have file : %s", filename);
        haveconfig = true;
        return true;
    }
    else
    {
        //เปิด file ใหม่
        configfile = SPIFFS.open(filename, "w");
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
String Configfile::getConfig(String valuename)
{
    loadConfig();
    return doc[valuename];
}
void Configfile::saveConfig()
{
    File file = SPIFFS.open(filename, "w");
    char buf[CONFIGFILE_buffersize];
    serializeJsonPretty(doc, buf, CONFIGFILE_buffersize);
    file.printf("%s\n", buf);
    file.close();
}
int Configfile::loadConfig()
{
    doc.clear();
    if (SPIFFS.exists(filename))
    {
        File file = SPIFFS.open(filename, "r");
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