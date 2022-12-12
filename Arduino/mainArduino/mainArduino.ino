#include <AccelStepper.h>
#include <SoftwareSerial.h>
#include <TFMPlus.h>  // Include TFMini Plus Library v1.5.0
TFMPlus tfmP;         // Create a TFMini Plus object
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "WiFiEsp.h"

#define sm1_pin1 2
#define sm1_pin2 3
#define sm1_pin3 4
#define sm1_pin4 5

#define sm2_pin1 6
#define sm2_pin2 7
#define sm2_pin3 8
#define sm2_pin4 9

#define aroundInterval 12900  // 한바퀴 도는 시간
#define LIDARDATASIZE 36      // 한바퀴 동안 측정할 데이터 개수

char ssid[] = "AndroidHotspot2409";            // your network SSID (name)
char pass[] = "12345678";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
int reqCount = 0;                // number of requests received

WiFiEspServer server(80);

AccelStepper stepper1(4, sm1_pin1, sm1_pin3, sm1_pin2, sm1_pin4);
AccelStepper stepper2(4, sm2_pin1, sm2_pin3, sm2_pin2, sm2_pin4);

int16_t tfDist = 0;    // Distance to object in centimeters
int16_t tfFlux = 0;    // Strength or quality of return signal
int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip
char dist[11];
unsigned long currentMillis;
unsigned long previousMillis;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // initialize serial for ESP module
  Serial2.begin(115200);  // Initialize TFMPLus device serial port.
  delay(20);               // Give port time to initalize
  tfmP.begin(&Serial2);   // Initialize device library object and...
  // pass device serial port to the object.

  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  printWifiStatus();
  
  // start the web server on port 80
  server.begin();

  // Send some example commands to the TFMini-Plus
  // - - Perform a system reset - - - - - - - - - - -
  Serial.print( "Soft reset: ");
  if( tfmP.sendCommand( SOFT_RESET, 0))
  {
    Serial.print( "passed.\r\n");
  }
  else tfmP.printReply();

  delay(500);  // added to allow the System Rest enough time to complete

  // - - Display the firmware version - - - - - - - - -
  Serial.print( "Firmware version: ");
  if( tfmP.sendCommand( GET_FIRMWARE_VERSION, 0))
  {
    Serial.print(tfmP.version[ 0]); // print three single numbers
    Serial.print(tfmP.version[ 1]); // each separated by a dot
    Serial.print(tfmP.version[ 2]);
    Serial.println();
  }
  else tfmP.printReply();
  // - - Set the data frame-rate to 20Hz - - - - - - - -
  Serial.print( "Data-Frame rate: ");
  if( tfmP.sendCommand( SET_FRAME_RATE, FRAME_20))
  {
    Serial.print(FRAME_20);
    Serial.println();
  }
  else tfmP.printReply();
  
  delay(2000);
}

void loop() {

  String jsonstr = "";
  LidarDetectAround(jsonstr);
  SendDataWeb(jsonstr);
  
  

  delay(3000);
}

void SendDataWeb(const String& jsonstr){
  // listen for incoming clients
  WiFiEspClient client = server.available();
  if (client) {
    Serial.println("New client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          Serial.println("Sending response");
          
          // send a standard http response header
          // use \r\n instead of many println statements to speedup data send
          client.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"  // the connection will be closed after completion of the response
            "Refresh: 20\r\n"        // refresh the page automatically every 20 sec
            "\r\n");
          client.print("<!DOCTYPE HTML>\r\n");
          client.print("<html>\r\n");
          client.print("<h1>Lidar Data : " + jsonstr + "</h2>\r\n");
          client.print("</html>\r\n");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(100);

    // close the connection:
    client.stop();
    Serial.println("Client disconnected");
  }
}

int getDataLidar(){
  tfmP.getData( tfDist); // Get data from the device.
  Serial.print( "Dist : ");   // display distance,
  Serial.print(tfDist);
  Serial.println( "cm");
  return tfDist;
}

void LidarDetectAround(String& jsonstr){
  previousMillis = millis();
  unsigned long lidarInterval = aroundInterval / LIDARDATASIZE;
  unsigned long lidarRunMillis = millis();
  
  StaticJsonDocument<40 + 10 * LIDARDATASIZE> doc;
  JsonObject root = doc.to<JsonObject>();
  JsonArray LidarData = root.createNestedArray("LidarData");
  int dataCount = 0;
  while(true){
    currentMillis = millis();
    if(currentMillis - previousMillis >= aroundInterval) break;
    if((currentMillis - lidarRunMillis)>= lidarInterval){
      lidarRunMillis += lidarInterval;
      if(dataCount >= LIDARDATASIZE - 1){
        Serial.println("ERROR: Lidar data Overflow!!!");
        break;
      }
      LidarData[dataCount] = getDataLidar();
      dataCount++;
    }
    RightRound();
  }
  Serial.println("==============");
  serializeJsonPretty(doc, jsonstr);
  Serial.println(jsonstr);
  Serial.println("==============");
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  // print where to go in the browser
  Serial.println();
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
  Serial.println();
}

void Stop(){
  stepper1.setSpeed(0);
  stepper2.setSpeed(0);
}

void Go(){
  stepper1.setSpeed(-1000);
  stepper2.setSpeed(1000);
  stepper1.runSpeed();
  stepper2.runSpeed();
}

void RightRound(){
  stepper1.setSpeed(500);
  stepper2.setSpeed(500);
  stepper1.runSpeed();
  stepper2.runSpeed();
}

void LeftRound(){
  stepper1.setSpeed(-500);
  stepper2.setSpeed(-500);
  stepper1.runSpeed();
  stepper2.runSpeed();
}
