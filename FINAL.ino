const int pingPin = 7;
// Function: If the sound sensor senses a sound that is up to the threshold you set in the code, the LED is on for 200ms.
// Hardware: Grove - Sound Sensor, Grove - LED
int sensorPin = 1; //the analog pin the TMP36's Vout (sense) pin

#include <Servo.h>// for servo

Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position 

/*macro definitions of the sound sensor and the LED*/
#define SOUND_SENSOR A0
#define LED 13      // the number of the LED pin

#define THRESHOLD_VALUE 100//The threshold to turn the led on 400.00*5/1024 = 1.95v

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(2);  // attaches the servo on pin 2 to the servo object
  pinMode(9, OUTPUT);
  beep(50);
  beep(50);
  beep(50);
  delay(1000);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pins_init();
  // for debugging, wait until a serial console is connected
  delay(4000);
  while(!Serial);
  
}


void loop() {
  //--added code
  //getting the voltage reading from the temperature sensor
    int reading = analogRead(sensorPin);
    // converting that reading to voltage, for 3.3v arduino use 3.3
    float voltage = reading * 5.0;
    voltage /= 1024.0;
    // print out the voltage
    Serial.print(voltage); Serial.println(" volts");
    // now print out the temperature
    float temperatureC = (voltage - 0.5) * 100 ; //converting from 10 mv per degree wit 500 mV offset
    //to degrees ((voltage - 500mV) times 100)
    Serial.print(temperatureC); Serial.println(" degrees C");
    // now convert to Fahrenheit
    float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
    Serial.print(temperatureF); Serial.println(" degrees F");
    delay(1000); //waiting a second
  
  //---sound sensor 
  int sensorValue = analogRead(SOUND_SENSOR);//use A0 to read the electrical signal
  Serial.print("sensorValue ");
  Serial.println(sensorValue);
  if(sensorValue > THRESHOLD_VALUE)
  {
  turnOnLED();//if the value read from A0 is larger than 400,then light the LED
  delay(200);
  }
  turnOffLED();
  
  // put your main code here, to run repeatedly:
 long duration, inches, cm;
  beep(200); 
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  
  

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
   if (108 > inches && inches > 73) 
 {
   digitalWrite(11, HIGH);
 }   
 else if (inches > 37) 
{
  digitalWrite(12, HIGH);
        
}   
else if (inches > 1) 
{
  digitalWrite(13, HIGH);
  
  // PLACED THE CODE TO ACTIVATE SERVO IF TEMP IS LESS THAN 90 AND INCHES IS LESS THAN
        if ((sensorValue > THRESHOLD_VALUE) && (temperatureF < 95.0))
      {
          Serial.print("In if: "); Serial.println(temperatureF);
          for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
          {                                  // in steps of 1 degree 
            myservo.write(pos);              // tell servo to go to position in variable 'pos' 
            delay(5);                       // waits 15ms for the servo to reach the position 
          } 
     for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
          {                                
            myservo.write(pos);              // tell servo to go to position in variable 'pos' 
            delay(3);                       // waits 15ms for the servo to reach the position 
           }
      }//close IF statement
} 
else
{ 
  digitalWrite (11, LOW), digitalWrite (12, LOW), digitalWrite (13, LOW);
}        
  delay(10);
}

void pins_init()
{
pinMode(LED, OUTPUT);
pinMode(SOUND_SENSOR, INPUT); 
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void beep(unsigned char delayms){
  analogWrite(9, 20);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(9, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
}  

void turnOnLED()
{
digitalWrite(LED,HIGH);
}
void turnOffLED()
{
digitalWrite(LED,LOW);
}
