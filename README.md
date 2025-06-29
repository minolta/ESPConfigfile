<h1>ใช้สำหรับบันทึก config ต่างๆลงใน file</h1>

<h1>use</h1>
แก้ใข platformio.ini

lib_deps = https://github.com/minolta/ESPConfigfile.git

<h1>วิธีใช้</h1>
<code>
#include "Configfile.h"


Configfile cfg("/config.cfg"); // "/config.cfg" เป็นชื่อที่เราจะเก็บ config
Configfile cfg1("/config1.cfg");


  cfg.setbuffer(configsize); //configzie เป็นขนาดของ buffer
  cfg1.setbuffer(200); //small config file 200 byte
  if (!cfg.openFile())
  {
    initconfig(); //ถ้าเป็น file ใหม่จะ return flase ตอน ope
  }

  

</code>
  <h1>เวลาดึงข้อมูลจาก file</h1>
<code>
  String config =  cfg.getConfig("configname","defaultifnotfound");

  int configint = cfg.getIntConfig("configname",10); //ถ้าไม่มี configname จะได้ 10 มาแทน
  double configdobuleorfloat = cfg.getDoubleConfig("configname",33.22);
</code>
  <h1>เพิ่ม config</h1>

  <code>
  cfg.setConfig("configname","value"); //ถ้ามีอยู่แล้วจะเขียนทับอันเดิมถ้าไม่มีจะเพิ่มใหม่
  </code>

  <h1>ดึงขอมูลทั้งออกมาเป็น json</h1>
<code>
  DynamicJsonDocument dy = cfg.getAll();
  JsonObject documentRoot = dy.as<JsonObject>();
</code>
<h1>remove config</h1>

cfg.remove("configname");


  

  
