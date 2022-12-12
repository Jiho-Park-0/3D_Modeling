
#include <TFMPlus.h>  // Include TFMini Plus Library v1.5.0
TFMPlus tfmP;         // Create a TFMini Plus object

#include <SoftwareSerial.h>

int16_t tfDist = 0;    // Distance to object in centimeters
int16_t tfFlux = 0;    // Strength or quality of return signal
int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip
char dist[11];


void setup() {
  Serial.begin(9600);      // Give port time to initalize
  Serial.print("\r\nTFMPlus Library Example - 10SEP2021\r\n");  // say 'hello'

  Serial1.begin(115200);  // Initialize TFMPLus device serial port.
  delay(20);               // Give port time to initalize
  tfmP.begin(&Serial1);   // Initialize device library object and...
  // pass device serial port to the object.

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
  delay(20);   // Loop delay to match the 20Hz data frame rate
  if( tfmP.getData( tfDist, tfFlux, tfTemp)) // Get data from the device.
  {
    Serial.print( "Dist : ");   // display distance,
    Serial.print(tfDist);
    Serial.print( "cm Flux : ");   // display signal strength/quality,
    Serial.print(tfFlux);
    Serial.print( "Temp : ");   // display temperature,
    Serial.print(tfTemp);
    Serial.println("C");
  }
  else                  // If the command fails...
  {
    tfmP.printFrame();  // display the error and HEX dataa
  }
}
