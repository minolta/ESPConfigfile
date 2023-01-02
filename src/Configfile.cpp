#include "Configfile.h"

Configfile::Configfile()
{
    filename = "/config.cfg";
}
Configfile::Configfile(String c)
{
    filename = c;
}
#if defined(ESP32)
void Configfile::setconfigwww(AsyncWebServerRequest *request)
{
    if (request->hasArg("configname"))
    {
        String configname = request->arg("configname");
        String value = request->arg("value");
        this->addConfig(configname, value);
        request->send(200, "application/json", "{\"Update\":\"" + configname + "\",\"to\":" + value + "\"}");
    }
    else
        request->send(500, "application/json", "{\"ERROR\":\"Noupdate\"}");
}
void Configfile::allconfigwww(AsyncWebServerRequest *request)
{
    DynamicJsonDocument d = this->getAll();
    char buf[bufferconfig];
    serializeJson(d, buf, bufferconfig);
    request->send(200, "application/json", buf);
}
#endif
boolean Configfile::haveAlreadyConfig()
{
    return haveconfig;
}
void Configfile::setbuffer(int v)
{
    bufferconfig = v;
}
int Configfile::configsize(void)
{
    DynamicJsonDocument d = load();
    return d.size();
}
/**
 * ถ้า return true แสดงว่ามี file อยู่แล้ว
 * ถ้า return false แสดงว่าไม่มี file อยู่เป็นการสร้าง config ใหม่
 * **/
boolean Configfile::openFile(void)
{
#if defined(ESP32)
    if (!LITTLEFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting LITTLEFS");
        open = false;
        return open;
        // return;
    }
    else
    {
        open = true;
    }
    if (LITTLEFS.exists(filename.c_str()))
    {
        Serial.printf("Have file : %s", filename.c_str());
        haveconfig = true;
        return true;
    }
    else
    {
        //เปิด file ใหม่
        configfile = LITTLEFS.open(filename.c_str(), "w");
        configfile.printf("%s\n", "new file");
        configfile.close();
        haveconfig = true;
        return false;
    }
#else
    if (!LittleFS.begin())
    {
        Serial.println("An Error has occurred while mounting LITTLEFS");
        open = false;
        return open;
        // return;
    }
    else
    {
        open = true;
    }
    if (LittleFS.exists(filename.c_str()))
    {
        Serial.printf("Have file : %s", filename.c_str());
        haveconfig = true;
        return true;
    }
    else
    {
        //เปิด file ใหม่
        configfile = LittleFS.open(filename.c_str(), "w");
        configfile.printf("%s\n", "new file");
        configfile.close();
        haveconfig = true;
        return false;
    }
#endif
}
String Configfile::getfilename(void)
{
    return filename;
}
void Configfile::addConfig(String valuename, String value)
{
    // doc.clear();
    // if (haveconfig)
    // {
        DynamicJsonDocument d = load();
        d[valuename] = value;
        // = value;
        Serial.printf("xxxxxxxxxxxxxx Size %d xxxxxxxxxxxxxxxx",d.capacity());
        serializeJsonPretty(d, Serial);
        Serial.println("xxxxxxxxxxxxxxxxxxxxxxxxxxxx");
        saveConfig(d);
    // }
}
void Configfile::addConfig(String valuename, int value)
{
    DynamicJsonDocument d = load();
    d[valuename] = value;
    saveConfig(d);
}
void Configfile::addConfig(String valuename, long value)
{

    DynamicJsonDocument d = load();
    d[valuename] = value;
    saveConfig(d);
}
void Configfile::addConfig(String valuename, double value)
{
    DynamicJsonDocument d = load();
    d[valuename] = value;
    saveConfig(d);
}
void Configfile::remove(String key)
{
    DynamicJsonDocument d = load();
    d.remove(key);
    saveConfig(d);
}
DynamicJsonDocument Configfile::getAll()
{
    DynamicJsonDocument d = load();
    return d;
}
String Configfile::getConfig(String valuename)
{
    DynamicJsonDocument d = load();
    return d[valuename];
}
int Configfile::getIntConfig(String valuename)
{
    DynamicJsonDocument d = load();
    String t = d[valuename];
    if (t)
    {
        return t.toInt();
    }

    return 0;
}
int Configfile::getIntConfig(String valuename, String defaultvalue)
{
    DynamicJsonDocument d = load();
    if (!d.containsKey(valuename))
        return defaultvalue.toInt();
    String t = d[valuename];
    if (t)
    {
        return t.toInt();
    }

    return defaultvalue.toInt();
}
int Configfile::getIntConfig(String valuename, int defaultvalue)
{
    DynamicJsonDocument d = load();
    if (!d.containsKey(valuename))
        return defaultvalue;
    String t = d[valuename];
    if (t)
    {
        return t.toInt();
    }

    return defaultvalue;
}
double Configfile::getDobuleConfig(String valuename)
{
    DynamicJsonDocument d = load();
    if (!d.containsKey(valuename))
        return 0;
    String t = d[valuename];
    return t.toDouble();
}
double Configfile::getDobuleConfig(String valuename, String defaultvalue)
{
    DynamicJsonDocument d = load();
    if (!d.containsKey(valuename))
        return defaultvalue.toDouble();
    String t = d[valuename];
    double p = t.toDouble();
    if (p == 0.00)
        return defaultvalue.toDouble();
    return p;
}
/**
 *
 * Reset to default remove file
 */
void Configfile::resettodefault(void)
{
#if defined(ESP32)
    LITTLEFS.remove(filename);
    delay(1000);
#else
    LittleFS.remove(filename);
    delay(1000);
#endif
}
double Configfile::getDobuleConfig(String valuename, double defaultvalue)
{
    DynamicJsonDocument d = load();
    if (!d.containsKey(valuename))
        return defaultvalue;
    String t = d[valuename];
    double p = t.toDouble();
    if (p == 0.00)
        return defaultvalue;
    return p;
}
String Configfile::getConfig(String valuename, String defaultvalue)
{
    DynamicJsonDocument d = load();
    String t = d[valuename];
    if (!d.containsKey(valuename))
        return defaultvalue;
    return d[valuename];
}
void Configfile::saveConfig()
{
}
void Configfile::saveConfig(DynamicJsonDocument d)
{
#if defined(ESP32)

    File file = LITTLEFS.open(filename.c_str(), "w");
    serializeJson(d, file);
    file.close();
#else
    File file = LittleFS.open(filename.c_str(), "w");
    // serializeJsonPretty(d, Serial);
    // Serial.println(d);
    serializeJson(d, file);
    file.close();
#endif
}
int Configfile::getBuffersize()
{
    return bufferconfig;
}
DynamicJsonDocument Configfile::load()
{
#if defined(ESP32)
    File file = LITTLEFS.open(filename.c_str(), "r");
    DynamicJsonDocument o(bufferconfig);
    deserializeJson(o, file);
    file.close();
    return o;
#else
    File file = LittleFS.open(filename.c_str(), "r");
    DynamicJsonDocument o(bufferconfig);
    deserializeJson(o, file);
    file.close();
    return o;
#endif
}