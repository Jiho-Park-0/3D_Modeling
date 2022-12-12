#include <ArduinoJson.h>

void setup(){
  Serial.begin(9600);
}

void loop(){
  StaticJsonDocument<384> doc;
  JsonObject root = doc.to<JsonObject>();

  JsonArray data = root.createNestedArray("data");
  //JsonArray data = doc["data"];
  data[0] =  1;
  data[1] =  2;
  data[2] =  3;

  String str = "";
  serializeJsonPretty(doc, str);
  Serial.println(str);
  delay(5000);
}
