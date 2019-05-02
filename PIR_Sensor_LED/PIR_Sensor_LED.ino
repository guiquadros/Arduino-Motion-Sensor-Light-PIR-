/*
* PIR sensor tester
*/

//pins
int ledPin = 13; // choose the pin for the LED
int inputPin = 2; // choose the input pin (for PIR sensor)
int val = 0; // variable for reading the PIR sensor OUT pin status
int currentVal = LOW; //controls current state of LED

//time
float oldTime = 0;
float elapsedTime = 0;
float delayTime = 10000;

void setup() {
	pinMode(ledPin, OUTPUT); // declare LED as output
	pinMode(inputPin, INPUT); // declare sensor as input
	Serial.begin(9600);
}

void loop() {
  if (currentVal == HIGH) {
    elapsedTime += getDeltaTime();
  }
  
	val = digitalRead(inputPin); // read input value
  
	Serial.println("val = " + String(val) 
	  + " | elapsedTime = " + String(elapsedTime) 
	  + " | delayTime = " + delayTime 
	  + " | currentVal = " + String(currentVal)
	);

  if (val == HIGH) {
    currentVal = HIGH;
    elapsedTime = 0;
  }
  else if (elapsedTime > delayTime) {
    currentVal = LOW;
    elapsedTime = 0;
  }
  
  digitalWrite(ledPin, currentVal);
}

float getDeltaTime(){
  float currentTime = millis();
  float deltaTime = currentTime - oldTime;
  oldTime = currentTime;
  return deltaTime;
}
