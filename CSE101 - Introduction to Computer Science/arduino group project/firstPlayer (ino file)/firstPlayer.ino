/*
| GTU CSE101 PROJECT
| GROUP 12
|
| Contributors of Code : Semih Dervis , Ismail Ayvaz , Osmancan Bozali , Tugrul Gurses 
|
| Turn-Based Point Guess Game on Matrix
|
*/

// First Player

// Necessary headers of components and flow of game
#include <MD_MAX72xx.h>
#include <LiquidCrystal_I2C.h>
#include "math.h"
#include "pitches.h"

// Speaker pin
#define SPEAKER_PIN 8

// Joystick pins
#define VERT_PIN A0
#define HORZ_PIN A1
#define SEL_PIN  2

// Matrix pins
#define	CS_PIN		10
#define	MAX_DEVICES	1

// Matrix setup
const int maxX = MAX_DEVICES * 8 - 1; // Determining borders of the 8x8 matrix
const int maxY = 7;

MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::PAROLA_HW, CS_PIN, MAX_DEVICES); // Creating matrix object

// LCD setup
#define I2C_ADDR    0x3f
#define LCD_COLUMNS 16
#define LCD_LINES   2

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);  // Creating LCD object

// Determining flags for flow control
enum GAME_STATE {
  INTRO, PIXEL_SELECTION, WAIT,
  
  FIND_PIXEL, GAMEOVER_WIN, GAMEOVER_LOSE,      

  BACK_TO_START, GET_PIXEL
};

GAME_STATE flag = INTRO;  // Initiating flag as INTRO for start


// Global variables

int x = 0; // Player's X position
int y = 0; // Player's Y position

int initial = 0;  // Variables for position comparison
int final = 0;    // Variables for position comparison

int targetX = 0; // Opponent's X position
int targetY = 0; // Opponent's Y position

int a = 0;
int b = 0;

int first_x = 0; // X position before player's movement
int first_y = 0; // Y position before player's movement

// Moves cursor on matrix
void pixelMotion(){

  int horz = analogRead(HORZ_PIN);
  int vert = analogRead(VERT_PIN);

  if (vert < 300) {
    y = min(y + 1, maxY);             
    tone(SPEAKER_PIN, NOTE_DS5);
    delay(50);
    noTone(SPEAKER_PIN);
  }
  if (vert > 700) {
    y = max(y - 1, 0);
    tone(SPEAKER_PIN, NOTE_DS5);
    delay(50);
    noTone(SPEAKER_PIN);
  }
  if (horz > 700) {
    x = min(x + 1, maxX);
    tone(SPEAKER_PIN, NOTE_DS5);
    delay(50);
    noTone(SPEAKER_PIN);
  }
  if (horz < 300) {
    x = max(x - 1, 0);
    tone(SPEAKER_PIN, NOTE_DS5);
    delay(50);
    noTone(SPEAKER_PIN);
  }
  mx.clear();
  mx.setPoint(y, x, true);
  mx.update();
  delay(50);
}

// Sets matrix cursor to a random position
void randomPosition() {
  if (a == 0) {
    x = random(maxX + 1);
    y = random(maxY + 1);
    first_x = x;
    first_y = y;
    mx.clear();
    mx.setPoint(y, x, true);
    mx.update();
    a = 1;
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("your turn");
  }
}

// Buzzer respond for farther guess of position
void coldSound(){
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("cold");
  tone(SPEAKER_PIN, NOTE_DS5);
  delay(300);
  tone(SPEAKER_PIN, NOTE_D5);
  delay(300);
  tone(SPEAKER_PIN, NOTE_CS5);
  delay(300);
  for (byte i = 0; i < 10; i++) {
    for (int pitch = -10; pitch <= 10; pitch++) {
      tone(SPEAKER_PIN, NOTE_C5 + pitch);
      delay(5);
    }
  }
  noTone(SPEAKER_PIN);
  lcd.clear();
}

// Buzzer respond for closer guess of position
void hotSound(){
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("hot");
  tone(SPEAKER_PIN, NOTE_E4);
  delay(150);
  tone(SPEAKER_PIN, NOTE_G4);
  delay(150);
  tone(SPEAKER_PIN, NOTE_E5);
  delay(150);
  tone(SPEAKER_PIN, NOTE_C5);
  delay(150);
  tone(SPEAKER_PIN, NOTE_D5);
  delay(150);
  tone(SPEAKER_PIN, NOTE_G5);
  delay(150);
  noTone(SPEAKER_PIN);
  lcd.clear();
}

// Buzzer respond for same guess of position
void sameSound(){
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("same");
  tone(SPEAKER_PIN, NOTE_C5);
  delay(150);
  tone(SPEAKER_PIN, NOTE_D5);
  delay(150);
  noTone(SPEAKER_PIN);
  lcd.clear();
}

void nokia() {
  tone(SPEAKER_PIN, NOTE_E5);
  delay(150);
  tone(SPEAKER_PIN, NOTE_D5);
  delay(150);
  tone(SPEAKER_PIN, NOTE_FS4);
  delay(300);  
  tone(SPEAKER_PIN, NOTE_GS4);
  delay(300);
  tone(SPEAKER_PIN, NOTE_CS5);
  delay(150);
  tone(SPEAKER_PIN, NOTE_B4);
  delay(150);
  tone(SPEAKER_PIN, NOTE_D4);
  delay(300);
  tone(SPEAKER_PIN, NOTE_E4);
  delay(300);
  tone(SPEAKER_PIN, NOTE_B4);
  delay(150);
  tone(SPEAKER_PIN, NOTE_A4);
  delay(150);
  tone(SPEAKER_PIN, NOTE_CS4);
  delay(300);
  tone(SPEAKER_PIN, NOTE_E4);
  delay(300);
  tone(SPEAKER_PIN, NOTE_A4);
  delay(600);
  noTone(SPEAKER_PIN);
}

// Informs opponent Arduoino about guess of player
void trueSelection(){
  Serial.println(1);
}

// Informs opponent Arduino about guess of player
void falseSelection(){
  Serial.println(0);
  flag = WAIT;
}

// Checks if opponent guessed right, if not, game continues
void wait(){
  if(flag == WAIT){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("opponent's turn");
    if(Serial.available() != 0) Serial.read(); // Pass the newline character
    while(Serial.available() == 0); // Waits for opponent's input
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("your turn");
    if(Serial.parseInt() == 1){    
      flag = GAMEOVER_LOSE;
    }
    else if(Serial.parseInt() == 0){  // Game continues as opponent's guess and player's position don't match
      flag = FIND_PIXEL;
    }
  }
}

// Displays intro screen
void intro() {
  if (flag == INTRO) {
    lcd.setCursor(3, 0);
    lcd.print("welcome to");
    lcd.setCursor(4, 1);
    lcd.print("the game");
    delay(1000);
    flag = PIXEL_SELECTION;
  }
}

// Sets opponent's pixel as target values of position
void getPixel(){
  if (flag == GET_PIXEL){
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("wait your");
    lcd.setCursor(3, 1);
    lcd.print("opponent");
    while(Serial.available() > 0) Serial.read();
    while(Serial.available() == 0); // Waits for opponent's X position
    targetX = Serial.parseInt();
    while(Serial.available() > 0) Serial.read();
    while(Serial.available() == 0); // Waits for opponent's Y position
    targetY = Serial.parseInt();
    flag = FIND_PIXEL;
  }
}

// Initializes player's position and sends it via serial port to opponent Arduino
void pixelSelection(){
  if (flag == PIXEL_SELECTION) {
    if (b == 0){
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("select a pixel");
      b = 1;
    }
    pixelMotion();
    if (digitalRead(SEL_PIN) == LOW) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("pixel selected");
      lcd.setCursor(4, 1);
      lcd.print("and sent");
      Serial.println(x);
      Serial.println(y);
      delay(1000);
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.print("make your guess!");
      flag = GET_PIXEL;
    }
  }
}

// Guesses opponent's position
void findPixel() {
  if (flag == FIND_PIXEL) {
    initial = pow(first_x - targetX, 2) + pow(first_y - targetY, 2);
    randomPosition();
    pixelMotion();
    if (digitalRead(SEL_PIN) == LOW) {
      first_x = x;
      first_y = y;
      final = pow(x - targetX, 2) + pow(y - targetY, 2);
      if(x == targetX && y == targetY){
        trueSelection();
        flag = GAMEOVER_WIN;
      }
      else if (final > initial){
        coldSound();
        falseSelection();
      } 
      else if (final < initial){
        hotSound();
        falseSelection();
      }
      else{
        sameSound();
        falseSelection();
      }
    }
  }
}

// Displays gameover screen depending on guess
void gameOver(){
  if (flag == GAMEOVER_WIN) {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("you win");
    flag = BACK_TO_START;
    nokia();
  }
  if (flag == GAMEOVER_LOSE) {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("you lose");
    nokia();
    flag = BACK_TO_START;  
  }
}

// Displays game-end screen
void backToStart(){
  if (flag == BACK_TO_START) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("game starts");
    lcd.setCursor(3, 1);
    lcd.print("again : 3");
    delay(1000);
    lcd.setCursor(3, 1);
    lcd.print("again : 2");
    delay(1000); 
    lcd.setCursor(3, 1);
    lcd.print("again : 1");
    delay(1000);
    lcd.setCursor(3, 1);
    lcd.print("again : 0");
    delay(1000);
    lcd.clear();
    a = 0;
    b = 0;
    flag = INTRO;       
  }
}

void setup() {
  // Seed for random()
  randomSeed(analogRead(A3));
  
  // Baudrate setup
  Serial.begin(9600);

  // Matrix setup
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 2);
  mx.clear();

  // Joystick setup
  pinMode(VERT_PIN, INPUT);
  pinMode(HORZ_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);

  // Initializing LCD
  lcd.init();
  lcd.backlight();

  x = random(maxX + 1);
  y = random(maxY + 1);


}

void loop() {
  intro();
  getPixel();               // Loops
  pixelSelection();         // Game
  findPixel();              // All Over
  wait();                   // Again ...
  gameOver();
  backToStart();
}