/*
 * Safe Temperature below - 98.6
 */

/// OneWire
/*
 * Digital 2 - dataBus ( yellow )
 * 5v - Vcc ( Red )
 * GND - GND ( Black )
 * 
 * 5v - 4.7k resistor - dataBus
 * 5v - Vcc
 * 
 * 
 */

/// RGB LED
/*
 * Longest - GND
 * Longest is 2nd. 1-R, 3-G, 4-B
 * R->9, G->10, B->11
 * 220 ohm to all
 * positive to all R, G and B through 220 ohm.
 */

 /// Buzzer
 /*
  * + 3
  */

#include<OneWire.h>
#include<DallasTemperature.h>

// Data wire is connected to Arduino digital pin 2
#define ONE_WIRE_BUS 2

// Setup an oneWire instance to communicate with any OneWire devices
OneWire oneWire( ONE_WIRE_BUS );

// pass oneWire reference to Dallas Temperature sensor
DallasTemperature sensors( &oneWire );

int pinR = 9, pinG = 10, pinB = 11, delayTime1 = 1000, cont = 0, cuPin, offPin1, offPin2, a_i, b_i, pinBuzzer = 3 ;
double cuTF;


void checkIt(){
  cuTF = sensors.getTempFByIndex( 0 );

  if( cuTF <= 96 ){
    cuPin = pinB;
    offPin1 = pinR;
    offPin2 = pinG;
  }
  else if ( cuTF >= 99 ){
    cuPin = pinR;
    offPin1 = pinG;
    offPin2 = pinB;
  }
  else{
    cuPin = pinG;
    offPin1 = pinR;
    offPin2 = pinB;
  }
  
}

void gotIt(){
  for( a_i=1; a_i<=10; a_i++ ){
    digitalWrite( cuPin, HIGH );
    //analogWrite( pinBuzzer, 200 );
    tone( pinBuzzer, 70, 50 );
    delay( 100 );
    digitalWrite( cuPin, LOW );
    //analogWrite( pinBuzzer, 0 );
  }
}

void light(){
  /*
  cont %= 3;
  if( cont == 0 ) cuPin = pinR;
  if( cont == 1 ) cuPin = pinG;
  if( cont == 2 ) cuPin = pinB;
  */

  if( cuPin == pinG ) gotIt();
  else
  digitalWrite( cuPin, HIGH );
  digitalWrite( offPin1, LOW );
  digitalWrite( offPin2, LOW );

  //delay( delayTime1 );
    
  cont++;
}



void setup() {

  /// LED
  pinMode( pinR, OUTPUT );
  pinMode( pinG, OUTPUT );
  pinMode( pinB, OUTPUT );

  /// Buzzer
  pinMode( pinBuzzer, OUTPUT );

  // Start serial communication for debugging purpose
  Serial.begin( 9600 );

  // Start up the library
  sensors.begin();

}

void loop() {

  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures();

  Serial.print( "Celsius temperature : " );

  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.print( sensors.getTempCByIndex( 0 ) );
  Serial.print( " - Fahrenheit temperature : " );
  Serial.println( sensors.getTempFByIndex( 0 ) );

  //Check it.
  checkIt();

  //delay( 1000 );

  light();

  //delay( delayTime1 );

}
