#include <Adafruit_NeoPixel.h>

#define voltDisplay 11           // the PWM pin the LED is attached to
#define brightness 0    // how bright the LED is
#define fadeAmount 3    // how many points to fade the LED by

// Sensor 1
// Echo 2
#define teamOneEcho 2
// Trig 3
#define teamOneTrig 3

// Sensor 2
// Echo 7
#define teamTwoEcho 7 
// Trig 6
#define teamTwoTrig 6

// Win distance
# define winDistance 20

// LED Pin
#define LED_PIN 9

//LED Count
#define LED_COUNT 60

//Declare strip
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


#define DEBUG false

long durationOne, durationTwo, distanceOne, distanceTwo;
int teamTwoScore = 0, teamOneScore = 0, displayScore = 0;
boolean ballReset = true;


// the setup routine runs once when you press reset:
void setup() {
  Serial.begin (9600);
  // declare pin 11 to be an output:
  pinMode(voltDisplay, OUTPUT);
  //Sensor 1 setup
  pinMode(teamOneTrig, OUTPUT);
  pinMode(teamOneEcho, INPUT);
  //Sensor 2 setuo
  pinMode(teamTwoTrig, OUTPUT);
  pinMode(teamTwoEcho, INPUT);
  // Pixels
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50);
}

// the loop routine runs over and over again forever:
void loop() {

  // Read sensor 1
  digitalWrite(teamOneTrig, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(teamOneTrig, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(teamOneTrig, LOW);
  durationOne = pulseIn(teamOneEcho, HIGH);
  distanceOne = (durationOne/2) / 29.1;

  // Distance write one
  if (DEBUG){
    Serial.print("Sensor one: ");
    Serial.print(distanceOne);
    Serial.println();
  }
  delay(100);

  // Read sensor 2
  digitalWrite(teamTwoTrig, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(teamTwoTrig, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(teamTwoTrig, LOW);
  durationTwo = pulseIn(teamTwoEcho, HIGH);
  distanceTwo = (durationTwo/2) / 29.1;

  // Distance write two
  if(DEBUG){
    Serial.print("Sensor two: ");
    Serial.print(distanceTwo);
    Serial.println();
 
    Serial.print("Ball reset:");
    Serial.println(ballReset);
  }
  // Check if there was a score
  if(distanceOne < winDistance && ballReset == true){
    Serial.println("Team two score!");
     teamTwoScore = teamTwoScore + 1;
     ballReset = false;
     point(2);
  }
  else if(distanceTwo < winDistance && ballReset == true){
    Serial.println("Team one score!");
    teamOneScore = teamOneScore + 1;
    ballReset = false;
    point(1);
  }
  else if(distanceTwo > winDistance && distanceOne > winDistance && ballReset == false){
    ballReset = true;
    strip.clear();
    strip.show();
  }
  else if(ballReset == false){
    Serial.println("Please remove the ball and place it on the playing field.");
  }


  delay(100);

  // Show score
  // if team a > team b, show -3
  // if team a < team b, show +3
  displayScore = (teamOneScore - teamTwoScore) + 3;
  analogWrite(voltDisplay, 153*(0.166667*displayScore));
  delay(100);

  if(abs(teamOneScore - teamTwoScore) >= 3){
    if(teamOneScore > teamTwoScore){
      Serial.println("Team one wins!");
      win(1);
    }
    else {
      Serial.println("Team two wins!");
      win(2);
    }
    teamOneScore = 0;
    teamTwoScore = 0;
  }
  
}

void point(int team){
  int i = 0;
  strip.clear();
  if (team == 1){
    for(i; i<LED_COUNT/2; i++) { // For each pixel...
      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      strip.setPixelColor(i, strip.Color(0, 150, 0));
      strip.show();   // Send the updated pixel colors to the hardware.
    }
  }
  else{
    i = LED_COUNT/2;
    for(i; i<LED_COUNT; i++) { // For each pixel...
      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      strip.setPixelColor(i, strip.Color(150, 0, 0));
      strip.show();   // Send the updated pixel colors to the hardware.
    }
  }
  
}

void win(int team){
  int upperLimit = LED_COUNT; 
  int lowerLimit = 0;
  if (team == 1){
    upperLimit = LED_COUNT/2;
  }
  else{
    lowerLimit = LED_COUNT/2;
  }
  
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i= lowerLimit; i<upperLimit; i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
  }
}
