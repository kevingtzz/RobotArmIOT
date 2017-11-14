#include <Servo.h>

Servo spin, arm1, arm2, arm3, grip;

const int maxgrip = 70;
const int mingrip = 18; 
const int maxarm1 = 150;
const int minarm1 = 10;

int pot = A0;
int val;

void setup() {

  spin.attach(16); //D0
  arm1.attach(5);  //D1
  arm2.attach(4);  //D2
  arm3.attach(0);  //D3
  grip.attach(2);  //D4

  delay(100);
  spin.write(0);
  delay(100);
  arm1.write(90);
  delay(100);
  arm2.write(0);
  delay(100);
  arm3.write(90);
  delay(100);
  grip.write(mingrip);
  delay(100);

  delay(100);

  val = analogRead(pot);
}

void loop() {

    //delay(100);
    
  /*  for (int i = 0; i < 180; ++i) {
      spin.write(i);
      delay(80);
    }

    for (int i = 180; i > 0; --i) {
      spin.write(i);
      delay(80);
    }

    for (int i = minarm1; i < maxarm1; ++i) {
      arm1.write(i);
      delay(80);
    }

     for (int i = maxarm1; i > minarm1; --i) {
      arm1.write(i);
      delay(80);
    }

      for (int i = 0; i < 180; ++i) {
      arm2.write(i);
      delay(100);
    }
      arm2.write(0);
      delay(1000);

      for (int i = 0; i < 180; ++i) {
      arm3.write(i);
      delay(100);
    }
      arm3.write(0);
      delay(1000);

     for (int i = mingrip; i < maxgrip; ++i) {
      grip.write(i);
      delay(100);
    }
      grip.write(mingrip);
      */
      val = analogRead(pot);
      val = map(val,0,1023,0,180);
      grip.write(val);
      //delay(1000);
}
