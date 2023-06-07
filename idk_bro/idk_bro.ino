#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>
#define ROLL_THRESHOLD  30 // Total acceleration threshold for roll detect

float X, Y, Z, totalAccel, soundPressure;

volatile int pixelNumber = 0;
volatile int colorControl = 0;
volatile int m = 0;
volatile int p = 0;



volatile int playerPixelColor = 0;
volatile int playerPixelZeroColor = 0;
volatile int playerPixelOneColor = 0;
volatile int playerPixelTwoColor = 0;
volatile int playerPixelThreeColor = 0;
volatile int playerPixelFourColor = 0;
volatile int playerPixelFiveColor = 0;
volatile int playerPixelSixColor = 0;
volatile int playerPixelSevenColor = 0;
volatile int playerPixelEightColor = 0;
volatile int playerPixelNineColor = 0;

AsyncDelay delay_1s;
AsyncDelay delay_10s;
AsyncDelay delay_20s; 

volatile int t = 0;
volatile int totalPoints = 0;

volatile int randomPixelZero= 0; 
volatile int randomPixelOne = 0;
volatile int randomPixelTwo = 0;
volatile int randomPixelThree = 0;
volatile int randomPixelFour = 0; 
volatile int randomPixelFive = 0;
volatile int randomPixelSix = 0;
volatile int randomPixelSeven = 0;
volatile int randomPixelEight = 0; 
volatile int randomPixelNine = 0;


int colors[] = {0xFF0000, 0xFF4500, 0xFFA500, 0x00FF00, 0x0000FF, 0xA020F0, 0xFF1493, 0xFFC0CB};

volatile int level = 0;
byte buttonA = 4;
byte buttonB = 5;
byte switchPin = 7;

volatile bool buttonFlagA = 0;
volatile bool buttonFlagB = 0; 
volatile bool switchState = 0;
volatile bool switchFlag = 0; 

int attempt = 0;
volatile bool playerChoice = 0;

int tally = 0;
volatile bool checkPoints = 0;

float midi[127];
int A_four = 440; 

void ISRpoints() {
  checkPoints = 1;
}

void ISRplayer() {
  playerChoice = 1;
}

void ISRa() {
  buttonFlagA = 1;
}

void ISRb() {
  buttonFlagB = 1;
}

void onOff() {
  switchFlag = 1;
}

void generateMIDI()
{
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}

int sadSong[3][2] = {
    {60, 400},
    {60, 400},
    {60, 400},
  };

int winnerSong[16][2] = { 
    {74, 200},
    {74, 200},
    {74, 200},
    {74, 200},
  };

void setup() {
  Serial.begin(9600);
  generateMIDI();
  randomSeed(analogRead(0)); 
  CircuitPlayground.begin();
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
  pinMode(buttonA, INPUT_PULLDOWN);
  pinMode(buttonB, INPUT_PULLDOWN);
  pinMode(switchPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonA), ISRa, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonB), ISRb, FALLING);
  attachInterrupt(digitalPinToInterrupt(switchPin), onOff, CHANGE);
  attachInterrupt(digitalPinToInterrupt(attempt), ISRplayer, RISING);
  attachInterrupt(digitalPinToInterrupt(tally), ISRpoints, RISING);
  delay_1s.start(1000, AsyncDelay::MILLIS);
  delay_10s.start(10000, AsyncDelay::MILLIS);
  delay_20s.start(5000, AsyncDelay::MILLIS);
}

void loop() {
  // put your main code here, to run repeatedly:

if (switchFlag) {
  Serial.println("game on");
  delay(5);
  switchState = 1;
  switchFlag = 0;
}
 if (buttonFlagB) {
   m = 0;
   pixelNumber = ++p;
   Serial.println("pixelNumber+1");
   delay(5);
   if (pixelNumber > 9) {
     p = 0;
     Serial.println("back to first pixel");
   }
   buttonFlagB = 0;
   playerTurn();
 }
 if (buttonFlagA) {
   colorControl = m++;
   Serial.println("colorControl+1");
   delay(5);
   if (colorControl > 8) {
     m = 0;
     Serial.println("back to beginning");
   }
   buttonFlagA = 0;
   playerTurn();
 }

if (switchState) {
soundPressure = CircuitPlayground.mic.soundPressureLevel(10);

if (totalPoints < -10) {
  level = -1;
  Serial.println("game failed");
} else if (totalPoints < 10) {
  level = 0;
} else if (10 <= totalPoints < 20) {
  level = 1;
} else if (20 <= totalPoints < 30) {
 level = 2;
} else if (30 <= totalPoints < 40) {
 level = 3;
} else if (40 <= totalPoints < 50) {
 level = 4;
} else if (50 <= totalPoints < 60) {
 level = 5;
} else if (60 <= totalPoints < 70) {
 level = 6;
} else if (70 <= totalPoints < 80) {
 level = 7;
} else if (80 <= totalPoints < 90) {
 level = 8;
} else {
 level = 9;
}

switch (level) {
  case 0:
    levelZero();
    delay(1000);
    
    break;
  case 1:
    levelOne();
    break;
  case 2:
    levelTwo();
    break;
  case 3:
    levelThree();
    break;
  case 4:
    levelFour();
    break;
  case 5:
    levelFive();
    break;
  case 6:
    levelSix();
    break;
  case 7:
    levelSeven();
    break;
  case 8:
    levelEight();
    break;
  case 9:
    "winner!";
    break;
  default:
    break;
}
delay(1000);

if (soundPressure > 85) {
  tallyPoints();
}
}
}


void tallyPoints() {
   //
  Serial.println("Check Light Pattern");

if (playerPixelZeroColor = randomPixelZero) {
  totalPoints = t+1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
} else {
  totalPoints = t-1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
}
if (playerPixelOneColor = randomPixelOne) {
  totalPoints = t+1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
} else {
  totalPoints = t-1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
}
if (playerPixelTwoColor = randomPixelTwo) {
  totalPoints = t+1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
} else {
  totalPoints = t-1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
}
if (playerPixelThreeColor = randomPixelThree) {
  totalPoints = t+1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
} else {
  totalPoints = t-1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
}
if (playerPixelFourColor = randomPixelFour) {
  totalPoints = t+1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
} else {
  totalPoints = t-1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
}
if (playerPixelFiveColor = randomPixelFive) {
  totalPoints = t+1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
} else {
  totalPoints = t-1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
}
if (playerPixelSixColor = randomPixelSix) {
  totalPoints = t+1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
} else {
  totalPoints = t-1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
}
if (playerPixelSevenColor = randomPixelSeven) {
  totalPoints = t+1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
} else {
  totalPoints = t-1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
}
if (playerPixelEightColor = randomPixelEight) {
  totalPoints = t+1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
} else {
  totalPoints = t-1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
}
if (playerPixelNineColor = randomPixelNine) {
  totalPoints = t+1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
} else {
  totalPoints = t-1;
  Serial.print("Total Points: "); Serial.println(totalPoints);
}

}

void playerTurn() {
     switch(colorControl) { 
     case 0: //takes two button presses to get to case 1
      CircuitPlayground.setPixelColor(pixelNumber, colors[0]);
      playerPixelColor = 0;
      break;
     case 1:
      CircuitPlayground.setPixelColor(pixelNumber, colors[1]);
      playerPixelColor = 1;
      break;
     case 2:
      CircuitPlayground.setPixelColor(pixelNumber, colors[2]);
      playerPixelColor = 2;
      break;
     case 3:
      CircuitPlayground.setPixelColor(pixelNumber, colors[3]);
      playerPixelColor = 3;
      break;
     case 4: //takes two button presses to get to case 1
      CircuitPlayground.setPixelColor(pixelNumber, colors[4]);
      playerPixelColor = 4;
      break;
     case 5:
      CircuitPlayground.setPixelColor(pixelNumber, colors[5]);
      playerPixelColor = 5;
      break;
     case 6:
      CircuitPlayground.setPixelColor(pixelNumber, colors[6]);
      playerPixelColor = 6;
      break;
     case 7:
      CircuitPlayground.setPixelColor(pixelNumber, colors[7]);
      playerPixelColor = 7;
      break;
     case 8:
      CircuitPlayground.setPixelColor(pixelNumber, colors[8]);
      playerPixelColor = 8;
      break;
     default:
      break;
    }
  
  switch (pixelNumber) {
     case 0:
      Serial.print("Player Pattern");
      playerPixelZeroColor = playerPixelColor;
      break;
     case 1:
      Serial.print("Player Pixel 0 = "); Serial.println(playerPixelZeroColor);
      playerPixelOneColor = playerPixelColor;
      break;
     case 2:
      Serial.print("Player Pixel 1 = "); Serial.println(playerPixelOneColor);
      playerPixelTwoColor = playerPixelColor;
      break;
     case 3:
      Serial.print("Player Pixel 2 = "); Serial.println(playerPixelTwoColor);
      playerPixelThreeColor = playerPixelColor;
      break;
     case 4:
      Serial.print("Player Pixel 3 = "); Serial.println(playerPixelThreeColor);
      playerPixelFourColor = playerPixelColor;
      break;
     case 5:
      Serial.print("Player Pixel 4 = "); Serial.println(playerPixelFourColor);
      playerPixelFiveColor = playerPixelColor;
      break;
     case 6:
      Serial.print("Player Pixel 5 = "); Serial.println(playerPixelFiveColor);
      playerPixelSixColor = playerPixelColor;
      break;
     case 7:
      Serial.print("Player Pixel 6 = "); Serial.println(playerPixelSixColor);
      playerPixelSevenColor = playerPixelColor;
      break;
     case 8:
      Serial.print("Player Pixel 7 = "); Serial.println(playerPixelSevenColor);
      playerPixelEightColor = playerPixelColor;
      break;
     case 9:
      Serial.print("Player Pixel 8 = "); Serial.println(playerPixelEightColor);
      playerPixelNineColor = playerPixelColor;
      tally = 1;
      break;
    default:
      break;
  } 
 
  delay(5000);
}

void checkShaking() {
  X = 0;
  Y = 0;
  Z = 0;
  for (int i=0; i<10; i++) {
    X += CircuitPlayground.motionX();
    Y += CircuitPlayground.motionY();
    Z += CircuitPlayground.motionZ();
    delay(1);
  }
  X /= 10;
  Y /= 10;
  Z /= 10;

  totalAccel = sqrt(X*X + Y*Y + Z*Z);
}

void levelZero() {
  checkShaking();

if (totalAccel > ROLL_THRESHOLD) {
    Serial.println("level zero");
    Serial.println("shake detected");
  for (int i = 0; i < 10; i++) {
    int randomColor = random(0,level);
  switch (i) {
    case 0:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelZero = randomColor;
      Serial.print("randomPixelZero = "); Serial.println(randomColor);
      break;
    case 1:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelOne = randomColor;
      Serial.print("randomPixelOne = "); Serial.println(randomColor);
      break;
    case 2:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelTwo = randomColor;
      Serial.print("randomPixelTwo = "); Serial.println(randomColor);
    case 3: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelThree = randomColor;
      Serial.print("randomPixelThree = "); Serial.println(randomColor);
    case 4: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFour = randomColor;
      Serial.print("randomPixelFour = "); Serial.println(randomColor);
    case 5: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFive = randomColor;
      Serial.print("randomPixelFive = "); Serial.println(randomColor);
    case 6: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSix = randomColor;
      Serial.print("randomPixelSix = "); Serial.println(randomColor);
    case 7: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSeven = randomColor;
      Serial.print("randomPixelSeven = "); Serial.println(randomColor);
    case 8: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelEight = randomColor;
      Serial.print("randomPixelEight = "); Serial.println(randomColor);
    case 9: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelNine = randomColor;
      Serial.print("randomPixelNine = "); Serial.println(randomColor);
      delay(500);
      playerChoice = 1;
      
    default:

      break;
  }
  delay(100);
  }
  delay(1000);
  CircuitPlayground.clearPixels();
  
  delay(500);
}
}

void levelOne() {
  checkShaking();

if (totalAccel > ROLL_THRESHOLD) {
    Serial.println("level one");
    Serial.println("shake detected");
  for (int i = 0; i < 10; i++) {
    int randomColor = random(0,level);
  switch (i) {
    case 0:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelZero = randomColor;
      Serial.print("randomPixelZero = "); Serial.println(randomColor);
      break;
    case 1:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelOne = randomColor;
      Serial.print("randomPixelOne = "); Serial.println(randomColor);
      break;
    case 2:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelTwo = randomColor;
      Serial.print("randomPixelTwo = "); Serial.println(randomColor);
    case 3: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelThree = randomColor;
      Serial.print("randomPixelThree = "); Serial.println(randomColor);
    case 4: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFour = randomColor;
      Serial.print("randomPixelFour = "); Serial.println(randomColor);
    case 5: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFive = randomColor;
      Serial.print("randomPixelFive = "); Serial.println(randomColor);
    case 6: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSix = randomColor;
      Serial.print("randomPixelSix = "); Serial.println(randomColor);
    case 7: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSeven = randomColor;
      Serial.print("randomPixelSeven = "); Serial.println(randomColor);
    case 8: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelEight = randomColor;
      Serial.print("randomPixelEight = "); Serial.println(randomColor);
    case 9: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelNine = randomColor;
      Serial.print("randomPixelNine = "); Serial.println(randomColor);
    default:

      break;
  }
  delay(100);
  }
  delay(1000);
  CircuitPlayground.clearPixels();
  delay(500);
}
  playerTurn();
}

void levelTwo() {
  checkShaking();

if (totalAccel > ROLL_THRESHOLD) {
    Serial.println("level two");
    Serial.println("shake detected");
  for (int i = 0; i < 10; i++) {
    int randomColor = random(0,level);
  switch (i) {
    case 0:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelZero = randomColor;
      Serial.print("randomPixelZero = "); Serial.println(randomColor);
      break;
    case 1:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelOne = randomColor;
      Serial.print("randomPixelOne = "); Serial.println(randomColor);
      break;
    case 2:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelTwo = randomColor;
      Serial.print("randomPixelTwo = "); Serial.println(randomColor);
    case 3: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelThree = randomColor;
      Serial.print("randomPixelThree = "); Serial.println(randomColor);
    case 4: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFour = randomColor;
      Serial.print("randomPixelFour = "); Serial.println(randomColor);
    case 5: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFive = randomColor;
      Serial.print("randomPixelFive = "); Serial.println(randomColor);
    case 6: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSix = randomColor;
      Serial.print("randomPixelSix = "); Serial.println(randomColor);
    case 7: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSeven = randomColor;
      Serial.print("randomPixelSeven = "); Serial.println(randomColor);
    case 8: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelEight = randomColor;
      Serial.print("randomPixelEight = "); Serial.println(randomColor);
    case 9: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelNine = randomColor;
      Serial.print("randomPixelNine = "); Serial.println(randomColor);
    default:

      break;
  }
  delay(100);
  }
  delay(1000);
  CircuitPlayground.clearPixels();
  delay(500);
}
}

void levelThree() {
  checkShaking();

if (totalAccel > ROLL_THRESHOLD) {
    Serial.println("level three");
    Serial.println("shake detected");
  for (int i = 0; i < 10; i++) {
    int randomColor = random(0,level);
  switch (i) {
    case 0:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelZero = randomColor;
      Serial.print("randomPixelZero = "); Serial.println(randomColor);
      break;
    case 1:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelOne = randomColor;
      Serial.print("randomPixelOne = "); Serial.println(randomColor);
      break;
    case 2:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelTwo = randomColor;
      Serial.print("randomPixelTwo = "); Serial.println(randomColor);
    case 3: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelThree = randomColor;
      Serial.print("randomPixelThree = "); Serial.println(randomColor);
    case 4: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFour = randomColor;
      Serial.print("randomPixelFour = "); Serial.println(randomColor);
    case 5: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFive = randomColor;
      Serial.print("randomPixelFive = "); Serial.println(randomColor);
    case 6: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSix = randomColor;
      Serial.print("randomPixelSix = "); Serial.println(randomColor);
    case 7: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSeven = randomColor;
      Serial.print("randomPixelSeven = "); Serial.println(randomColor);
    case 8: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelEight = randomColor;
      Serial.print("randomPixelEight = "); Serial.println(randomColor);
    case 9: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelNine = randomColor;
      Serial.print("randomPixelNine = "); Serial.println(randomColor);
    default:

      break;
  }
  delay(100);
  }
  delay(1000);
  CircuitPlayground.clearPixels();
  delay(500);
}
}

void levelFour() {
  checkShaking();

if (totalAccel > ROLL_THRESHOLD) {
    Serial.println("level four");
    Serial.println("shake detected");
  for (int i = 0; i < 10; i++) {
    int randomColor = random(0,level);
  switch (i) {
    case 0:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelZero = randomColor;
      Serial.print("randomPixelZero = "); Serial.println(randomColor);
      break;
    case 1:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelOne = randomColor;
      Serial.print("randomPixelOne = "); Serial.println(randomColor);
      break;
    case 2:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelTwo = randomColor;
      Serial.print("randomPixelTwo = "); Serial.println(randomColor);
    case 3: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelThree = randomColor;
      Serial.print("randomPixelThree = "); Serial.println(randomColor);
    case 4: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFour = randomColor;
      Serial.print("randomPixelFour = "); Serial.println(randomColor);
    case 5: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFive = randomColor;
      Serial.print("randomPixelFive = "); Serial.println(randomColor);
    case 6: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSix = randomColor;
      Serial.print("randomPixelSix = "); Serial.println(randomColor);
    case 7: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSeven = randomColor;
      Serial.print("randomPixelSeven = "); Serial.println(randomColor);
    case 8: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelEight = randomColor;
      Serial.print("randomPixelEight = "); Serial.println(randomColor);
    case 9: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelNine = randomColor;
      Serial.print("randomPixelNine = "); Serial.println(randomColor);
    default:

      break;
  }
  delay(100);
  }
  delay(1000);
  CircuitPlayground.clearPixels();
  delay(500);
}
}

void levelFive() {
  checkShaking();

if (totalAccel > ROLL_THRESHOLD) {
    Serial.println("level five");
    Serial.println("shake detected");
  for (int i = 0; i < 10; i++) {
    int randomColor = random(0,level);
  switch (i) {
    case 0:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelZero = randomColor;
      Serial.print("randomPixelZero = "); Serial.println(randomColor);
      break;
    case 1:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelOne = randomColor;
      Serial.print("randomPixelOne = "); Serial.println(randomColor);
      break;
    case 2:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelTwo = randomColor;
      Serial.print("randomPixelTwo = "); Serial.println(randomColor);
    case 3: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelThree = randomColor;
      Serial.print("randomPixelThree = "); Serial.println(randomColor);
    case 4: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFour = randomColor;
      Serial.print("randomPixelFour = "); Serial.println(randomColor);
    case 5: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFive = randomColor;
      Serial.print("randomPixelFive = "); Serial.println(randomColor);
    case 6: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSix = randomColor;
      Serial.print("randomPixelSix = "); Serial.println(randomColor);
    case 7: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSeven = randomColor;
      Serial.print("randomPixelSeven = "); Serial.println(randomColor);
    case 8: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelEight = randomColor;
      Serial.print("randomPixelEight = "); Serial.println(randomColor);
    case 9: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelNine = randomColor;
      Serial.print("randomPixelNine = "); Serial.println(randomColor);
    default:

      break;
  }
  delay(100);
  }
  delay(1000);
  CircuitPlayground.clearPixels();
  delay(500);
}
}

void levelSix() {
  checkShaking();

if (totalAccel > ROLL_THRESHOLD) {
    Serial.println("level six");
    Serial.println("shake detected");
  for (int i = 0; i < 10; i++) {
    int randomColor = random(0,level);
  switch (i) {
    case 0:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelZero = randomColor;
      Serial.print("randomPixelZero = "); Serial.println(randomColor);
      break;
    case 1:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelOne = randomColor;
      Serial.print("randomPixelOne = "); Serial.println(randomColor);
      break;
    case 2:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelTwo = randomColor;
      Serial.print("randomPixelTwo = "); Serial.println(randomColor);
    case 3: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelThree = randomColor;
      Serial.print("randomPixelThree = "); Serial.println(randomColor);
    case 4: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFour = randomColor;
      Serial.print("randomPixelFour = "); Serial.println(randomColor);
    case 5: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFive = randomColor;
      Serial.print("randomPixelFive = "); Serial.println(randomColor);
    case 6: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSix = randomColor;
      Serial.print("randomPixelSix = "); Serial.println(randomColor);
    case 7: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSeven = randomColor;
      Serial.print("randomPixelSeven = "); Serial.println(randomColor);
    case 8: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelEight = randomColor;
      Serial.print("randomPixelEight = "); Serial.println(randomColor);
    case 9: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelNine = randomColor;
      Serial.print("randomPixelNine = "); Serial.println(randomColor);
    default:

      break;
  }
  delay(100);
  }
  delay(1000);
  CircuitPlayground.clearPixels();
  delay(500);
}
}

void levelSeven() {
  checkShaking();

if (totalAccel > ROLL_THRESHOLD) {
    Serial.println("level seven");
    Serial.println("shake detected");
  for (int i = 0; i < 10; i++) {
    int randomColor = random(0,level);
  switch (i) {
    case 0:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelZero = randomColor;
      Serial.print("randomPixelZero = "); Serial.println(randomColor);
      break;
    case 1:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelOne = randomColor;
      Serial.print("randomPixelOne = "); Serial.println(randomColor);
      break;
    case 2:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelTwo = randomColor;
      Serial.print("randomPixelTwo = "); Serial.println(randomColor);
    case 3: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelThree = randomColor;
      Serial.print("randomPixelThree = "); Serial.println(randomColor);
    case 4: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFour = randomColor;
      Serial.print("randomPixelFour = "); Serial.println(randomColor);
    case 5: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFive = randomColor;
      Serial.print("randomPixelFive = "); Serial.println(randomColor);
    case 6: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSix = randomColor;
      Serial.print("randomPixelSix = "); Serial.println(randomColor);
    case 7: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSeven = randomColor;
      Serial.print("randomPixelSeven = "); Serial.println(randomColor);
    case 8: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelEight = randomColor;
      Serial.print("randomPixelEight = "); Serial.println(randomColor);
    case 9: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelNine = randomColor;
      Serial.print("randomPixelNine = "); Serial.println(randomColor);
    default:

      break;
  }
  delay(100);
  }
  delay(1000);
  CircuitPlayground.clearPixels();
  delay(500);
}
}

void levelEight() {
  checkShaking();

if (totalAccel > ROLL_THRESHOLD) {
    Serial.println("level Eight");
    Serial.println("shake detected");
  for (int i = 0; i < 10; i++) {
    int randomColor = random(0,level);
  switch (i) {
    case 0:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelZero = randomColor;
      Serial.print("randomPixelZero = "); Serial.println(randomColor);
      break;
    case 1:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelOne = randomColor;
      Serial.print("randomPixelOne = "); Serial.println(randomColor);
      break;
    case 2:
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelTwo = randomColor;
      Serial.print("randomPixelTwo = "); Serial.println(randomColor);
    case 3: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelThree = randomColor;
      Serial.print("randomPixelThree = "); Serial.println(randomColor);
    case 4: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFour = randomColor;
      Serial.print("randomPixelFour = "); Serial.println(randomColor);
    case 5: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelFive = randomColor;
      Serial.print("randomPixelFive = "); Serial.println(randomColor);
    case 6: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSix = randomColor;
      Serial.print("randomPixelSix = "); Serial.println(randomColor);
    case 7: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelSeven = randomColor;
      Serial.print("randomPixelSeven = "); Serial.println(randomColor);
    case 8: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelEight = randomColor;
      Serial.print("randomPixelEight = "); Serial.println(randomColor);
    case 9: 
      CircuitPlayground.setPixelColor(i, colors[randomColor]);
      randomPixelNine = randomColor;
      Serial.print("randomPixelNine = "); Serial.println(randomColor);
    default:

      break;
  }
  delay(100);
  }
  delay(1000);
  CircuitPlayground.clearPixels();
  delay(500);
}
}