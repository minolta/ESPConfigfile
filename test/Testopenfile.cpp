#include <Arduino.h>
#include <unity.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "Configfile.h"

void makedoc(void)
{
    DynamicJsonDocument doc(2048);
    char buf[2048];
    doc["ssid"] = "forpi";
    doc["password"] = "1234";

    if (!SPIFFS.begin(true))
        ;
    return;
    File file = SPIFFS.open("/config.cfg", "w");

    serializeJsonPretty(doc, buf, 2048);
    file.printf("%s\n", buf);
    file.close();

    TEST_ASSERT_EQUAL(true, SPIFFS.exists("/config.cfg"));

    return;
}

DynamicJsonDocument doc1(2048);
void loadConfig()
{
    File file = SPIFFS.open("/config.cfg", "r");
    String b = "";
    while (file.available())
    {
        b = b + String(file.readStringUntil('\n'));
    }
    file.close();
    deserializeJson(doc1, b.c_str());
}
void saveConfig()
{
    File file = SPIFFS.open("/config.cfg", "w");
    char buf[2048];
    serializeJsonPretty(doc1, buf, 2048);
    file.printf("%s\n", buf);
    file.close();
}
void readConfig(void)
{
    File file = SPIFFS.open("/config.cfg", "w");
    // char buf[2048];
    doc1["ssid"] = "forpi";
    doc1["password"] = "1234";

    if (!SPIFFS.begin(true))
    {
        return;
    }



    doc1["errortime"] = "1";
    saveConfig();
    doc1.clear();
    loadConfig();
    String d = doc1["ssid"];
    TEST_ASSERT_EQUAL_STRING("forpi", d.c_str());
    String e = doc1["errortime"];
    TEST_ASSERT_EQUAL_STRING("1", e.c_str());
}

void addConfig(String valuename,String value)
{
    doc1.clear();
    loadConfig();
    doc1[valuename] = value;
    saveConfig();
}
String getConfig(String valuename)
{
    loadConfig();
    return doc1[valuename];
}
void TestAddConfig(void)
{
    addConfig("D1init","1");

    loadConfig();

    String d1init = doc1["D1init"];
    TEST_ASSERT_EQUAL_STRING("1",d1init.c_str());
    

}

void TestGetvalue()
{
    addConfig("version","10");

    String version = getConfig("version");
    TEST_ASSERT_EQUAL_STRING("10",version.c_str());
}
void havefile(void)
{
    Configfile c;
    TEST_ASSERT_EQUAL(true,c.haveAlreadyConfig());
    // Configfile cfg =  Configfile();
    // TEST_ASSERT_EQUAL(true,cfg.haveAreadyConfig());
}
void setup()
{

  
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(makedoc);
    RUN_TEST(readConfig);
    RUN_TEST(TestAddConfig);
    RUN_TEST(TestGetvalue);
    RUN_TEST(havefile);
    // TEST_ASSERT_EQUAL_STRING("forpi", "x");
    // RUN_TEST(test_function_calculator_subtraction);
    // RUN_TEST(test_function_calculator_multiplication);
    // RUN_TEST(test_function_calculator_division);
    TEST_ASSERT_EQUAL(true, SPIFFS.begin(true));
    // TEST_ASSERT_EQUAL(true, makedoc);
    // readConfig();
    // String d = doc1["ssid"];
    // TEST_ASSERT_EQUAL_STRING("forpi", d.c_str());

    UNITY_END();
}

void loop()
{
    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(2, LOW);
    delay(500);
}