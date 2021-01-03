#include <Arduino.h>
#include "Configfile.h"

Configfile cf("/x1122.cfg");
/**
 * 
 * 
 * Update getIntConfig with default value 
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start");
  Serial.printf("\nOpen file is ok %d\n",cf.openFile());
  Serial.printf("Have config ? %d\n",cf.haveAlreadyConfig());
  // String c = cf.getConfig("xx");

  cf.openFile();
  cf.getConfig("X","x");
  cf.addConfig("d",200.00);
  //  Serial.printf("xx: %s\n",c);
  // cf.addConfig("xx","sss");

  Serial.println("End fix buf begin()");
  // Serial.println(cf.haveAlreadyConfig());
}

void loop() {
  // put your main code here, to run repeatedly:
}