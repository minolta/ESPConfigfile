<h1>ใช้สำหรับบันทึก config ต่างๆลงใน file สำหรับ esp 8266 esp32</h1>

<h1>use</h1>
แก้ใข platformio.ini

lib_deps = https://github.com/minolta/ESPConfigfile.git

<h1>วิธีใช้</h1>

```cpp
#include "Configfile.h"


Configfile cfg("/config.cfg"); // "/config.cfg" เป็นชื่อที่เราจะเก็บ config
Configfile cfg1("/config1.cfg");
Configfile *c;



  cfg.setbuffer(configsize); //configzie เป็นขนาดของ buffer
  cfg1.setbuffer(200); //small config file 200 byte
  if (!cfg.openFile())
  {
    initconfig(); //ถ้าเป็น file ใหม่จะ return flase ตอน ope
  }

c = new Configfile("/c");
c->setbuffer(2024);
c->openFile();
int intvaluewithdefault = c->getIntConfig("configname",10);
float v = c->getDoubleConfig("floatconfigname"); //get without default
```
<h1>เวลาดึงข้อมูลจาก file</h1>

```cpp
String config =  cfg.getConfig("configname","defaultifnotfound");
int configint = cfg.getIntConfig("configname",10); //ถ้าไม่มี configname จะได้ 10 มาแทน
double configdobuleorfloat = cfg.getDoubleConfig("configname",33.22);  ```
```

<h1>เพิ่ม config</h1>

```cpp  
  cfg.setConfig("configname","value"); //ถ้ามีอยู่แล้วจะเขียนทับอันเดิมถ้าไม่มีจะเพิ่มใหม่
```

  <h1>ดึงขอมูลทั้งหมดออกมาเป็น json</h1>
 
 ```cpp
  DynamicJsonDocument dy = cfg.getAll();
  JsonObject documentRoot = dy.as<JsonObject>();
  String tr = "";
    for (JsonPair keyValue : documentRoot)
    {
      String v = dy[keyValue.key()];
      String k = keyValue.key().c_str();
      tr += "<tr><td>" + k + "</td><td> <label id=" + k + "value>" + v + "</label> </td> <td> <input id = " + k + " value =\"" + v + "\"></td><td><button id=btn onClick=\"setvalue(this,'" + k + "','" + v + "')\">Set</button></td><td><button id=btn onClick=\"remove('" + k + "')\">Remove</button></td></tr>";
    }
    tr += "<tr><td>heap</td><td colspan=4>" + String(ESP.getFreeHeap()) + "</td></tr>";


  String getsomevalue = documentRoot["configname"];
```

<h1>remove config</h1>
 
 ```cpp
cfg.remove("configname");

```
  

  
