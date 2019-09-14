/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fade
*/

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
  }
  else if(distanceTwo < winDistance && ballReset == true){
    Serial.println("Team one score!");
    teamOneScore = teamOneScore + 1;
    ballReset = false;
  }
  else if(distanceTwo > winDistance && distanceOne > winDistance && ballReset == false){
    ballReset = true;  
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
    }
    else {
      Serial.println("Team two wins!");
    }
    teamOneScore = 0;
    teamTwoScore = 0;
  }
  // Display test
 /* for(int i = 0; i<=6; i++){
    analogWrite(voltDisplay, 153*(0.166667*i));
    delay(3000);
  }*/
  
}
