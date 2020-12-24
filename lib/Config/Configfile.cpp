#include "Configfile.h"

Configfile::Configfile()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        open = false;
        return;
    }

    if (SPIFFS.exists("/config.cfg"))
    {
        open = true;
        doc.clear();
        haveconfig = true;
        loadConfig();
    }
    else
    {
        haveconfig = false;
    }

    // configfile = SPIFFS.open("/config.cfg", "r");
}
boolean Configfile::haveAlreadyConfig()
{
    return haveconfig;
}
void Configfile::addConfig(String valuename, String value)
{
    doc.clear();
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
    File file = SPIFFS.open("/config.cfg", "w");
    char buf[CONFIGFILE_buffersize];
    serializeJsonPretty(doc, buf, CONFIGFILE_buffersize);
    file.printf("%s\n", buf);
    file.close();
}
void Configfile::loadConfig()
{

    File file = SPIFFS.open("/config.cfg", "r");
    String b = "";
    while (file.available())
    {
        b = b + String(file.readStringUntil('\n'));
    }
    file.close();
    deserializeJson(doc, b.c_str());
}