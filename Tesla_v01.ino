/*

   This is the Arduino code to control speed of motor using L293d DC motor Driver
   This code will control the motor with different direction and speed type

  Watch instruction for this video: https://youtu.be/akQoGNUzhHI


  // Written by Ahmad S. for Robojax.com on
  // on Aug 11, 2018 at 13:23 at city of Ajax, Ontario, Canada
  // This code is AS is without warranty. You can share if you keep this note with the code
*/
// DC motor  control
#define P1A 10 // define pin 10as for P1A
#define P2A 5 // define pin 11 as for P2A
#define EN12 12 // define pin 9 as for 1,2EN enable

#define P1B 11 // define pin 10as for P1A
#define P2B 6 // define pin 11 as for P2A
#define EN34 8 // define pin 9 as for 1,2EN enable


#define  trig 3  // define the triger for the ultrasonic sensor
#define  echo 2  // define the echo input of the Sensor

long travel_time, distance;



const int max_dis = 40; // 40 sm maximum acceptable distance
const int speedStep = 15;
const int speedDelay = 1000;// delay between speed increment



void setup() {
  // L293 Motor Contro Code by Robojax.com 20180811
  Serial.begin(9600);// setup Serial Monitor to display information

  pinMode(P1A, OUTPUT);// define pin as OUTPUT for P1A
  pinMode(P2A, OUTPUT);// define pin as OUTPUT for P2A
  pinMode(EN12, OUTPUT);// define pin as OUTPUT for 1,2EN

  pinMode(P1B, OUTPUT);// define pin as OUTPUT for P1A
  pinMode(P2B, OUTPUT);// define pin as OUTPUT for P2A
  pinMode(EN34, OUTPUT);// define pin as OUTPUT for 1,2EN


  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  Serial.println("L293D Motor Speed Control");


}

void loop() {

  Serial.println("New Loop");

  if (ObsticalDetection()) {
    forward(255, 1);
    delay(500);
  }
  forward(0, 0);


  //
  //backward(255, 1);
  //delay(1000);
  //
  //backward(255, 0);
  //
  //turn('L');
  //delay(1000);
  //turn('R');
  //delay(1000);


}//loop end


bool ObsticalDetection() {

  Serial.println("obstical detection is called");

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  //Sending a high puls
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  travel_time = pulseIn(echo, HIGH);

  //calculation the distance

  distance = (travel_time * 0.034) / 2 ; // Distance = Time * Speed / 2
  // The speed of sound is 340.29 m/s or 0.034 cm/µs.
  Serial.println(distance);
  if (distance > max_dis)
    return true;
  else
    return false;
}

void forward (int spd, int en) {

  digitalWrite(EN12 , en); // Enable 1A and 2A
  analogWrite(P1A, spd); // send PWM with spd value to P1A
  digitalWrite(P2A, LOW); // LOW signal to P2A

}

void backward (int spd, int en) {

  digitalWrite(EN12 , en); //enable 1A and 2A
  digitalWrite(P1A, LOW); // Keep it LOW P1A
  analogWrite(P2A, spd); // send PWM with spd value to  P2A

}

void turn(char dir) {

  if (dir == 'L') {

    digitalWrite(EN34 , 1); // Enable 1A and 2A
    analogWrite(P1B, 250); // send PWM with spd value to P1A
    digitalWrite(P2B, LOW); // LOW signal to P2A

  } else {

    digitalWrite(EN34 , 1); //enable 1A and 2A
    digitalWrite(P1B, LOW); // Keep it LOW P1A
    analogWrite(P2B, 250); // send PWM with spd value to  P2A



  }

}
