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
    // doc.clear();
    if (haveconfig)
    {
        DynamicJsonDocument d = load();
        d[valuename] = value;
        saveConfig(d);
    }
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
    String t = d[valuename];
    return t.toDouble();
}
double Configfile::getDobuleConfig(String valuename, String defaultvalue)
{
    DynamicJsonDocument d = load();
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
    SPIFFS.remove(filename);
    delay(1000);
}
double Configfile::getDobuleConfig(String valuename, double defaultvalue)
{
    DynamicJsonDocument d = load();
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
    // Serial.printf("\n getdefault : %d %s\n", value, value);
    // if (value.equals("null"))
    // {
    // return defaultvalue;
    // }
    // return value;
}
void Configfile::saveConfig()
{
    // File file = SPIFFS.open(filename.c_str(), "w");
    // char buf[CONFIGFILE_buffersize];
    // serializeJsonPretty(doc, buf, CONFIGFILE_buffersize);
    // file.printf("%s\n", buf);
    // file.close();
}
void Configfile::saveConfig(DynamicJsonDocument d)
{
    File file = SPIFFS.open(filename.c_str(), "w");
    serializeJsonPretty(d, file);
    file.close();
}
// int Configfile::loadConfig()
// {
//     doc.clear();
//     if (SPIFFS.exists(filename.c_str()))
//     {
//         File file = SPIFFS.open(filename.c_str(), "r");
//         String b = "";
//         while (file.available())
//         {
//             b = b + String(file.readStringUntil('\n'));
//         }
//         file.close();
//         deserializeJson(doc, b.c_str(), CONFIGFILE_buffersize);
//         return 1;
//     }
//     else
//     {
//         return 0;
//     }
// }

DynamicJsonDocument Configfile::load()
{

    File file = SPIFFS.open(filename.c_str(), "r");
    DynamicJsonDocument o(CONFIGFILE_buffersize);
    deserializeJson(o, file);
    file.close();
    return o;
}