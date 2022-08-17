#include <LiquidCrystal.h> //LCD Screen

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;


LiquidCrystal lcd(8,9,10,11,12,13); //LCD

const unsigned short tasksNum = 2; // Number of Tasks
task tasks[tasksNum];
const unsigned long ButtonPeriod = 325;
const unsigned long UltrasonicPeriod = 100;
enum ButtonStates {ButtonStart, NoButton, ButtonPress, ButtonHold} bstate;
enum UltrasonicStates {UStart, UCheck} ustate;
const unsigned char j_size = 9;
const unsigned char i_size = 6;
unsigned int bellFlag = 0;
unsigned int motionFlag = 0;
int i = 0;
int j = 0;
float distance_inch = 0;
long duration = 0;

const double tones[i_size][j_size] = //Door Bell Tones
{
{261.63,293.66,329.63,349.23,392,440,493.88l,523.25,0},
{659.25,523.25,587.33,392,0,392,587.33,659.25,523.25},
{523.25,493.88l,440,392,349.32,329.63,293.66,261.63,0},
{261.63,277.18,293.66,311.13,329.63,349.23,369.99,392.00,415.30},
{261.63,329.63,392.00,523.25,0,523.25,392.00,329.63,261.63},
{415.30,392.00,369.99,349.23,329.63,311.13,293.66,277.18,261.63},
};

void setup() {
  pinMode(2, INPUT); //Button
  digitalWrite(2, HIGH);
  Serial.begin(9600);
  lcd.begin(16,2); //Set up LCD
  pinMode(3,OUTPUT); //Trig Pin Ultrasonic Sensor
  pinMode(4, INPUT); //Echo Pin Ultrasonic Sensor
  pinMode(5, OUTPUT); //Buzzer
  pinMode(6,OUTPUT); //Yellow-Orange LED
  pinMode(7,OUTPUT); //Red LED

  unsigned char i = 0;
  tasks[i].state = ButtonStart;
  tasks[i].period = ButtonPeriod;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &ButtonStates;
  ++i;
  tasks[i].state = UStart;
  tasks[i].period = UltrasonicPeriod;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &UltrasonicStates;
}

int ButtonStates(int bstate) {
  switch (bstate) {
    case ButtonStart:
      noTone(5);
      bstate = ButtonPress;
      break;
    case NoButton:
      if (!digitalRead(2) && motionFlag) //If Button Pressed
        bstate = ButtonPress;
      else
        bstate = NoButton;
      noTone(5);
      break;
    case ButtonPress:
      lcd.clear();
      if (j < j_size){ // Play through array
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        tone(5,tones[i][j]); // Play note
        j++; // Iterate
        lcd.setCursor(0,0);
        bellFlag = 1;
        lcd.print("Alert:Front Door");
        bstate = ButtonPress; //Stay in state until tune is done
      }
      else { // Finished playing through array
        noTone(5);
        lcd.clear();
        if (i < (i_size-1)) // If still more songs in array
          i++; //Move to next song
        else 
          i = 0; //Reset array
        j = 0; //Reset note in array
        bellFlag = 0;
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        bstate = ButtonHold;
      }
        break;
     case ButtonHold:
      if (!digitalRead(2))  //If Button Pressed
        bstate = ButtonHold;
      else
        bstate = NoButton;
      noTone(5);
      break;
    default:
      break;
  }

  switch (bstate) {
    default:
      break;
  }
  return bstate;
}

int UltrasonicStates(int ustate) {
  switch (ustate) {
    case UStart:
      ustate = UCheck;
      break;
    case UCheck:
      digitalWrite(3, LOW);
      delayMicroseconds(2);
      digitalWrite(3, HIGH);
      delayMicroseconds(10);
      digitalWrite(3, LOW);
      duration = pulseIn(4, HIGH);
      distance_inch = duration * 0.013464 / 2; 
      if (!bellFlag){
        if (distance_inch <= 10){ //If someone is within 5 inches of sensor
          motionFlag = 1;
          lcd.setCursor(0,0);
          lcd.print("Motion Alert: ");
          lcd.setCursor(0,1);
          lcd.print(distance_inch);
          lcd.print(" inches");
        }
        else{
          motionFlag = 0;
          lcd.clear();
        }
      }
      ustate = UCheck;
      break;
    default:
      break;
}
switch (ustate) {
    case UCheck:
      break;
    default:
      break;
  }
  return ustate;
}


void loop() {
  unsigned char i;
  unsigned long currentTime;
  currentTime = millis();
  for (i = 0; i < tasksNum; ++i) {
    if ( (currentTime - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = currentTime; 
    }
  }
}
