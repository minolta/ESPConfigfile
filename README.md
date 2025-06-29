<h1>ใช้สำหรับบันทึก config ต่างๆลงใน file</h1>


<h1>วิธีใช้</h1>

#include "Configfile.h"


Configfile cfg("/config.cfg"); // "/config.cfg" เป็นชื่อที่เราจะเก็บ config



  cfg.setbuffer(configsize); //configzie เป็นขนาดของ buffer
  if (!cfg.openFile())
  {
    initconfig(); //ถ้าเป็น file ใหม่จะ return flase ตอน ope
  }


  <h1>เวลาดึงข้อมูลจาก file</h1>

  String config =  cfg.getConfig("configname","defaultifnotfound");

  int configint = cfg.getIntConfig("configname",10); //ถ้าไม่มี configname จะได้ 10 มาแทน
  double configdobuleorfloat = cfg.getDoubleConfig("configname",33.22);

  <h1>เพิ่ม config</h1>

  
  cfg.setConfig("configname","value"); //ถ้ามีอยู่แล้วจะเขียนทับอันเดิมถ้าไม่มีจะเพิ่มใหม่


  <h1>ดึงขอมูลทั้งออกมาเป็น json</h1>

  DynamicJsonDocument dy = cfg.getAll();
  JsonObject documentRoot = dy.as<JsonObject>();

<h1>remove config</h1>

cfg.remove("configname");


  

  
