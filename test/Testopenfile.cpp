
#include <Arduino.h>
#include <unity.h>
// #define UNITY_INCLUDE_DOUBLE
// #define UNITY_DOUBLE_PRECISION 1e-12
// #include <LITTLEFS.h>
#include <ArduinoJson.h>
#include "Configfile.h"
void open(void)
{
    TEST_ASSERT_EQUAL(false, LITTLEFS.exists("/1111.cfg"));
}

void testLoad()
{
    Configfile cc("/xxxx.xf");
    cc.openFile();
    cc.addConfig("ADD", "10");
    DynamicJsonDocument d = cc.load();
    TEST_ASSERT_EQUAL_INT(1, d.size());
    String s = cc.getConfig("ADD");
    TEST_ASSERT_EQUAL_STRING("10", s.c_str());
    d["ADD"] = "20";
    cc.saveConfig(d);
    s = cc.getConfig("ADD");
    TEST_ASSERT_EQUAL_STRING("20", s.c_str());
}
void makedoc(void)
{
    DynamicJsonDocument doc(2048);
    char buf[2048];
    doc["ssid"] = "forpi";
    doc["password"] = "1234";

    if (!LITTLEFS.begin(true))
        ;
    return;
    File file = LITTLEFS.open("/config.cfg", "w");

    serializeJsonPretty(doc, buf, 2048);
    file.printf("%s\n", buf);
    file.close();

    TEST_ASSERT_EQUAL(true, LITTLEFS.exists("/config.cfg"));

    return;
}

DynamicJsonDocument doc1(2048);
void loadConfig()
{
    File file = LITTLEFS.open("/config.cfg", "r");
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
    File file = LITTLEFS.open("/config.cfg", "w");
    char buf[2048];
    serializeJsonPretty(doc1, buf, 2048);
    file.printf("%s\n", buf);
    file.close();
}
void readConfig(void)
{
    File file = LITTLEFS.open("/config.cfg", "w");
    // char buf[2048];
    doc1["ssid"] = "forpi";
    doc1["password"] = "1234";

    if (!LITTLEFS.begin(true))
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

void addConfig(String valuename, String value)
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
    addConfig("D1init", "1");

    loadConfig();

    String d1init = doc1["D1init"];
    TEST_ASSERT_EQUAL_STRING("1", d1init.c_str());
}

void TestGetvalue()
{
    addConfig("version", "10");

    String version = getConfig("version");
    TEST_ASSERT_EQUAL_STRING("10", version.c_str());
}
void havefile(void)
{
    Configfile c("/t.xf");
    c.openFile();
    //
    // TEST_ASSERT_EQUAL(true, c.haveAlreadyConfig());

    c.addConfig("1", "1");

    String v = c.getConfig("1");

    TEST_ASSERT_EQUAL_STRING("1", v.c_str());

    // Configfile cfg =  Configfile();
    // TEST_ASSERT_EQUAL(true,cfg.haveAreadyConfig());
}
void getFilename()
{
    Configfile cc("/getfilename.txt");
    TEST_ASSERT_EQUAL_STRING("/getfilename.txt", cc.getfilename().c_str());
}
void readValue()
{
    Configfile cc("/t.xf");
    cc.openFile();
    cc.addConfig("1", "1");
    cc.addConfig("ssid", "forpi");
    String v = cc.getConfig("1");
    String ssid = cc.getConfig("ssid");
    TEST_ASSERT_EQUAL_STRING("1", v.c_str());
    TEST_ASSERT_EQUAL_STRING("forpi", ssid.c_str());
}
void TestloadConfig()
{
    Configfile cc("/t1.xf");
    cc.openFile();
    DynamicJsonDocument d = cc.load();
    TEST_ASSERT_EQUAL(1, cc.openFile());
    cc.addConfig("1", "1");
    cc.addConfig("2", "2");
    cc.addConfig("3", "test");
    cc.addConfig("ssid", "forpi");
    // TEST_ASSERT_EQUAL(1, cc.loadConfig());
    //  cc.loadConfig();
    TEST_ASSERT_EQUAL(4, cc.configsize());
}
void Testloadall()
{
    Configfile cc("/t11.xf");
    cc.openFile();
    cc.addConfig("1", "1");
    cc.addConfig("2", "2");
    cc.addConfig("3", "test");
    DynamicJsonDocument d = cc.getAll();
    TEST_ASSERT_EQUAL(3, d.size());
}
void getDefault(void)
{

    Configfile cc("/config.cfg");
    cc.openFile();
    String value = cc.getConfig("testdefault1", "default");
    TEST_ASSERT_EQUAL_STRING("default", value.c_str());
}
void getDefaultAlreadyhave(void)
{

    Configfile cc("/config.cfg");
    cc.openFile();
    cc.addConfig("testdefault", "xxxx");
    String value = cc.getConfig("testdefault", "default");
    TEST_ASSERT_EQUAL_STRING("xxxx", value.c_str());
}
void addInt(void)
{
    Configfile cc("/config.cfg");
    cc.openFile();
    cc.addConfig("int", 1);

    String i = cc.getConfig("int", "222");

    TEST_ASSERT_EQUAL_STRING("1", i.c_str());
}
void addDouble(void)
{
    Configfile cc("/config.cfg");
    cc.openFile();
    cc.addConfig("double", 1.22);

    String i = cc.getConfig("double", "222");

    TEST_ASSERT_EQUAL_STRING("1.22", i.c_str());
}
void testDoublenull(void)
{
    Configfile cc("/config.cfg");
    cc.openFile();

    String p = cc.getConfig("11");

    double pp = p.toDouble();
    Serial.print("============== ");
    Serial.print(pp);
    // TEST_ASSERT_EQUAL_DOUBLE(0.00, pp);
}
void testNull(void)
{
    Configfile cc("/config.cfg");
    cc.openFile();

    cc.addConfig("int", 1);
    String p = cc.getConfig("int2");
    // int r = p.toInt();
    String p1 = cc.getConfig("int");
    int r = p1.toInt();
    Serial.println(r);

    TEST_ASSERT_EQUAL_INT(0, p.toInt());
    TEST_ASSERT_EQUAL_INT(1, r);
}
void testGetIntconfig(void)
{
    Configfile cc("/config.cfg");
    cc.openFile();

    cc.addConfig("intvalue", "1");
    int p = cc.getIntConfig("intvalue", "2");
    TEST_ASSERT_EQUAL_INT(1, p);
}
void testGetIntconfigbydefaultint(void)
{
    Configfile cc("/config.cfg");
    cc.openFile();

    cc.addConfig("intvalueint", "2");
    int p = cc.getIntConfig("intvalueint", 2);
    TEST_ASSERT_EQUAL_INT(2, p);
}
void testGetDoubleconfigbydefaultdouble(void)
{
    Configfile cc("/config.cfg");
    cc.openFile();

    cc.addConfig("doublevalue", "2.2");
    double p = cc.getDobuleConfig("doublevalue", 2.2);
    TEST_ASSERT_EQUAL_DOUBLE(2.2, p);
}
void setup()
{

    Serial.begin(9600);
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(testLoad);
    RUN_TEST(getDefaultAlreadyhave);
    RUN_TEST(testNull);
    RUN_TEST(testGetIntconfig);
    RUN_TEST(testGetIntconfigbydefaultint);
    RUN_TEST(testGetDoubleconfigbydefaultdouble);
    RUN_TEST(testDoublenull);
    RUN_TEST(addInt);
    RUN_TEST(addDouble);
    RUN_TEST(TestloadConfig);
    RUN_TEST(getDefault);
    RUN_TEST(open);
    RUN_TEST(Testloadall);
    RUN_TEST(getFilename);
    RUN_TEST(readValue);
    RUN_TEST(makedoc);
    RUN_TEST(readConfig);
    RUN_TEST(TestAddConfig);
    RUN_TEST(TestGetvalue);
    RUN_TEST(havefile);
    TEST_ASSERT_EQUAL(true, LITTLEFS.begin(true));
    UNITY_END();
}

void loop()
{
    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(2, LOW);
    delay(500);
}