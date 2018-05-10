#define intPin 8
#define myLed 13

uint16_t LED_TimeOn = 0;

void setup() {

  //Start UARTs
  Serial.begin(115200);
  Serial1.begin(115200);
  delay(4000);

  // Set up led output on Dragonfly
  pinMode(myLed, OUTPUT);
  digitalWrite(myLed, HIGH); // led is active LOW

  // Basic AT commands
  Serial1.write("AT\r");
  while(!Serial1.available() ) { delay(100); }
  Serial.write("AT working? "); 
  while ( Serial1.available() ) { Serial.write(Serial1.read() ); }
  Serial.println(" ");
  digitalWrite(myLed, LOW); delay(10); digitalWrite(myLed, HIGH);
 
  Serial1.write("ATVERHW\r");
  while(!Serial1.available() ) { delay(100); }
  Serial.write("Hardware version: "); 
  while ( Serial1.available() ) { Serial.write(Serial1.read() ); }
  Serial.println(" ");
  digitalWrite(myLed, LOW); delay(10); digitalWrite(myLed, HIGH);

  Serial1.write("ATVERSW\r");
  while(!Serial1.available() ) { delay(100); }
  Serial.write("Software version: "); 
  while ( Serial1.available() ) { Serial.write(Serial1.read() ); }
  Serial.println(" ");
  digitalWrite(myLed, LOW); delay(10); digitalWrite(myLed, HIGH);

  Serial1.write("ATPRES\r");
  while(!Serial1.available() ) { delay(100); }
  Serial.write("Number of devices present?: "); 
  while ( Serial1.available() ) { Serial.write(Serial1.read() ); }
  Serial.println(" ");
  digitalWrite(myLed, LOW); delay(10); digitalWrite(myLed, HIGH);

  Serial1.write("ATGAIN\r");
  while(!Serial1.available() ) { delay(100); }
  Serial.println("Default gain setting: "); 
  while ( Serial1.available() ) { Serial.write(Serial1.read() ); }
  Serial.println(" ");
  digitalWrite(myLed, LOW); delay(10); digitalWrite(myLed, HIGH);

  Serial1.write("ATGAIN=0\r");
  while(!Serial1.available() ) { delay(100); }
  Serial.println("Set gain to minimum setting: "); 
  while ( Serial1.available() ) { Serial.write(Serial1.read() ); }
  Serial.println(" ");
  digitalWrite(myLed, LOW); delay(10); digitalWrite(myLed, HIGH);

  Serial1.write("ATGAIN\r");
  while(!Serial1.available() ) { delay(100); }
  Serial.println("New gain setting: "); 
  while ( Serial1.available() ) { Serial.write(Serial1.read() ); }
  Serial.println(" ");
  digitalWrite(myLed, LOW); delay(10); digitalWrite(myLed, HIGH);

  Serial1.write("ATINTTIME\r");
  while(!Serial1.available() ) { delay(100); }
  Serial.println("Default integration time: "); 
  while ( Serial1.available() ) { Serial.write(Serial1.read() ); }
  Serial.println(" ");
  digitalWrite(myLed, LOW); delay(10); digitalWrite(myLed, HIGH);

  Serial1.write("ATINTTIME=36\r");
  while(!Serial1.available() ) { delay(100); }
  Serial.println("Set integration time to 100 ms: "); 
  while ( Serial1.available() ) { Serial.write(Serial1.read() ); }
  Serial.println(" ");
  digitalWrite(myLed, LOW); delay(10); digitalWrite(myLed, HIGH);

  Serial1.write("ATINTTIME\r");
  while(!Serial1.available() ) { delay(100); }
  Serial.println("New integration time: "); 
  while ( Serial1.available() ) { Serial.write(Serial1.read() ); }
  Serial.println(" ");
  digitalWrite(myLed, LOW); delay(10); digitalWrite(myLed, HIGH);

  Serial1.write("ATTEMP\r");
  while(!Serial1.available() ) { delay(100); }
  Serial.print("IC temperature of 1/2/3: "); 
  while ( Serial1.available() ) { Serial.write(Serial1.read() ); }
  Serial.println(" ");
  digitalWrite(myLed, LOW); delay(10); digitalWrite(myLed, HIGH);

  Serial.println("Waiting for more AT commands...");
}


void loop() {
     
     // Send bytes from AS7265X -> Dragonfly to Computer
    if ( Serial1.available() ) {
         digitalWrite(myLed, LOW);   // set the LED on
         LED_TimeOn = millis();
         Serial.write( Serial1.read() );
    }

    // Send bytes from Computer -> Dragonfly back to AS7265X
    if ( Serial.available() ) {
        digitalWrite(myLed, LOW);   // set the LED on
        LED_TimeOn = millis();
        Serial1.write( Serial.read() );
    }

    if (millis() - LED_TimeOn > 20) {
  digitalWrite(myLed, HIGH);        // set the LED off
  }
    if (millis() - LED_TimeOn > 20) {
  digitalWrite(myLed, HIGH);        // set the LED off
  }

}


