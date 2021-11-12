#include <HX711.h>
#include <LiquidCrystal.h>

HX711 scale;

LiquidCrystal lcd(8,9,4,5,6,7);
const int buttonPin = 7; // start sequence button
const int ledPin = 6; //LED indicator and/or buzzer
const int igniterPin = 11; //igniter transistor circuit
#define DOUT 3
#define CLK 2
float calibration_factor = 100000; //100000 worked for my 10kg max scale setup 
float conv_factor = 0.453592;  


void setup() {
 pinMode(buttonPin, INPUT_PULLUP);
 pinMode(igniterPin, OUTPUT);
 pinMode(ledPin, OUTPUT);
 Serial.begin(9600);
 Serial.println("HX711 Rocket Motor Dynamometer, V.5");
 Serial.println("Affix motor nozzle up. Place igniter in nozzle. Move away from test stand.");
 Serial.println("Press start button to initialize ignition sequence.");
 scale.begin(DOUT, CLK);
 scale.set_scale();
 scale.tare(); //Reset the scale to 0,
 long zero_factor = scale.read_average(); //Get a baseline reading
 Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
 Serial.println(zero_factor);
 Serial.println(" "); 
 Serial.println("Scale has been zeroed");
 Serial.println(" ");
 Serial.println("Before setting up the scale:");
 Serial.print("read: \t\t");
  Serial.println(scale.read());     // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

}

void loop() {
  boolean buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
  digitalWrite(ledPin, HIGH);
  delay (1000);
  digitalWrite (ledPin,LOW);
  delay (1000); 
  Serial.println("Test");
  digitalWrite (igniterPin,HIGH);
 }
scale.set_scale(calibration_factor); //Adjust to this calibration factor
Serial.println("Reading: ");
Serial.print("Raw: ");
Serial.println(scale.read());
Serial.print("Your '0': ");
Serial.print(scale.get_value());
Serial.print(" Your offset: ");
Serial.println(scale.get_offset());
//Serial.print(scale.get_units()*0.453592, );
Serial.print(scale.get_units()*conv_factor, 10);
Serial.print(" kg"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
Serial.print(" calibration_factor: ");
Serial.print(calibration_factor);
Serial.println();
delay(750);  
}  
