int motor1Pin1 = 27;
int motor1Pin2 = 26;
int motor2Pin1 = 33;
int motor2Pin2 = 25;
int motor3Pin1 = 2;
int motor3Pin2 = 0;
int motor4Pin1 = 22;
int motor4Pin2 = 23;
int motor5Pin1 = 19;
int motor5Pin2 = 13;
int motor6Pin1 = 14;
int motor6Pin2 = 21;

//first motor controller board
int buttonPin1 = 17;
int buttonPin2 = 16;
int buttonPin3 = 18;
int buttonPin4 = 5;

//second motor controller board
int buttonPin5 = 15;
int buttonPin6 = 32;

bool motor1Active = false;
bool motor2Active = false;
bool motor3Active = false;
bool motor4Active = false;
bool motor5Active = false;
bool motor6Active = false;

//general start time
unsigned long startTime;
//separate start time variable for test
unsigned long startTime1 = 0;
unsigned long startTime2 = 0;

//motor timing stages
unsigned long elapsedTimeMotor1;
unsigned long elapsedTimeMotor2;
unsigned long elapsedTimeMotor3;
unsigned long elapsedTimeMotor4;
unsigned long elapsedTimeMotor5;
unsigned long elapsedTimeMotor6;

//motor states
int motor1UpState = 0;
bool motor2UpState = 0;
bool motor3UpState = 0;
bool motor4UpState = 0;
bool motor5UpState = 0;
bool motor6UpState = 0;

//button states
bool button1State = 0;
bool button2State = 0;
bool button3State = 0;
bool button4State = 0;
bool button5State = 0;
bool button6State = 0;

const int freq = 30000;
const int pwmChannel = 0;
const int pwmChannel2 = 1;
const int pwmChannel3 = 2;
const int resolution = 8;
int dutyCycle = 170;

void setup() {
  Serial.begin(9600);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  // pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  // pinMode(enable2Pin, OUTPUT);

  //Motor pin 3
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);

  //Motor pin 4
  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);

  //Motor pin 5
  pinMode(motor5Pin1, OUTPUT);
  pinMode(motor5Pin2, OUTPUT);

  //Motor pin 6
  pinMode(motor6Pin1, OUTPUT);
  pinMode(motor6Pin2, OUTPUT);

  //button pins setup
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);

  //set stattime to millis
  startTime = millis();
}

void loop() {
  //set current time in the loop for testing
  unsigned long currentTime = millis();

  //control motor1 button click
  //if motor is not moving activate the button
  if (motor1Active == false) {
    button1State = digitalRead(buttonPin1);
  }
  //else disable the button - block clicking possibility
  else
    button1State = 2;

  //control motor2 button click - same as above
  if (motor2Active == false) {
    button2State = digitalRead(buttonPin2);
  } else button2State = 2;

  //control motor3 button click - same as above
  if (motor3Active == false) {
    button3State = digitalRead(buttonPin3);
  } else button3State = 2;

  //control motor4 button click - same as above
  if (motor4Active == false) {
    button4State = digitalRead(buttonPin4);
  } else button4State = 2;

  //control motor5 button click - same as above
  if (motor5Active == false) {
    button5State = digitalRead(buttonPin5);
  } else button5State = 2;

  //control motor6 button click - same as above
  if (motor6Active == false) {
    button6State = digitalRead(buttonPin6);
  } else button6State = 2;

  //NOTE
  //I tried 2 different methods of millis in the first if statement and in the 3rd if statement
  // the first if statement takes the millis general time from the loop
  //the third millis takes the variable from setup and count time based on the millis in the motor's if statement block

  //motor 1 controller code
  // if button is pressed or motor1 is moving one or the other direction
  if (button1State == 0 || motor1Active == true) {
    // set the motor to be active (if the button is pressed the motor variable unblocks the if statement to run in the loop)
    motor1Active = true;
    //check if the time difference is lesser then 3000ms - 3 seconds || check if the motor should move up or down
    if (currentTime - startTime1 <= 3000 && motor1UpState == true) {
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
    }
    //check if the time difference is lesser then 3000ms - 3 seconds || check if the motor should move up or down
    else if (currentTime - startTime1 <= 3000 && motor1UpState == false) {
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
    }
    //switch motor movement off - reset the time variale and post motor variable to false to enable button click again
    else {
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      //set start time as current
      startTime1 = currentTime;
      if (motor1UpState == 0) {
        motor1UpState = 1;
      } else motor1UpState = 0;
      motor1Active = false;
    }
  }

  //motor 2 controller code - same as above
  if (button2State == 0 || motor2Active == true) {
    motor2Active = true;
    // elapsedTimeMotor2 = millis();
    if (currentTime - startTime2 <= 3000 && motor2UpState == true) {
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
    } else if (currentTime - startTime2 <= 3000 && motor2UpState == false) {
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
    } else {
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
      //set start time as current
      startTime2 = currentTime;
      if (motor2UpState == 0) {
        motor2UpState = 1;
      } else motor2UpState = 0;
      motor2Active = false;
    }
  }

  //motor 3 controller code - other method of millis
  // if button is pressed or motor1 is moving one or the other direction
  if (button3State == 0 || motor3Active == true) {
    // set the motor to be active (if the button is pressed the motor variable unblocks the if statement to run in the loop)
    motor3Active = true;
    // get time in the local code block
    elapsedTimeMotor3 = millis();
    //check if the time difference is lesser then 3000ms - 3 seconds || check if the motor should move up or down
    if (elapsedTimeMotor3 - startTime <= 3000 && motor3UpState == true) {
      digitalWrite(motor3Pin1, LOW);
      digitalWrite(motor3Pin2, HIGH);
    }
    //check if the time difference is lesser then 3000ms - 3 seconds || check if the motor should move up or down
    else if (elapsedTimeMotor3 - startTime <= 3000 && motor3UpState == false) {
      digitalWrite(motor3Pin1, HIGH);
      digitalWrite(motor3Pin2, LOW);
    }
    //switch motor movement off - reset the time variale and post motor variable to false to enable button click again
    else {
      digitalWrite(motor3Pin1, LOW);
      digitalWrite(motor3Pin2, LOW);
      // set start time as code block time
      startTime = elapsedTimeMotor3;
      if (motor3UpState == 0) {
        motor3UpState = 1;
      } else motor3UpState = 0;
      motor3Active = false;
    }
  }

  //motor 4 controller code - same as above
  if (button4State == 0 || motor4Active == true) {
    motor4Active = true;
    elapsedTimeMotor4 = millis();
    if (elapsedTimeMotor4 - startTime <= 3000 && motor4UpState == true) {
      digitalWrite(motor4Pin1, HIGH);
      digitalWrite(motor4Pin2, LOW);
    } else if (elapsedTimeMotor4 - startTime <= 3000 && motor4UpState == false) {
      digitalWrite(motor4Pin1, LOW);
      digitalWrite(motor4Pin2, HIGH);
    } else {
      digitalWrite(motor4Pin1, LOW);
      digitalWrite(motor4Pin2, LOW);
      startTime = elapsedTimeMotor4;
      if (motor4UpState == 0) {
        motor4UpState = 1;
      } else motor4UpState = 0;
      motor4Active = false;
    }
  }

  //motor 5 controller code - same as above
  if (button5State == 0 || motor5Active == true) {
    motor5Active = true;
    elapsedTimeMotor5 = millis();
    if (elapsedTimeMotor5 - startTime <= 3000 && motor5UpState == true) {
      digitalWrite(motor5Pin1, HIGH);
      digitalWrite(motor5Pin2, LOW);
    } else if (elapsedTimeMotor5 - startTime <= 3000 && motor5UpState == false) {
      digitalWrite(motor5Pin1, LOW);
      digitalWrite(motor5Pin2, HIGH);
    } else {
      digitalWrite(motor5Pin1, LOW);
      digitalWrite(motor5Pin2, LOW);
      startTime = elapsedTimeMotor5;
      if (motor5UpState == 0) {
        motor5UpState = 1;
      } else motor5UpState = 0;
      motor5Active = false;
    }
  }

  //motor 6 controller code - same as above
  if (button6State == 0 || motor6Active == true) {
    motor6Active = true;
    elapsedTimeMotor6 = millis();
    if (elapsedTimeMotor6 - startTime <= 3000 && motor6UpState == true) {
      digitalWrite(motor6Pin1, HIGH);
      digitalWrite(motor6Pin2, LOW);
    } else if (elapsedTimeMotor6 - startTime <= 3000 && motor6UpState == false) {
      digitalWrite(motor6Pin1, LOW);
      digitalWrite(motor6Pin2, HIGH);
    } else {
      digitalWrite(motor6Pin1, LOW);
      digitalWrite(motor6Pin2, LOW);
      startTime = elapsedTimeMotor6;
      if (motor6UpState == 0) {
        motor6UpState = 1;
      } else motor6UpState = 0;
      motor6Active = false;
    }
  }
}