#include <mbed.h>

#define pirPin PF_13
#define userButtonPin PC_13
#define UserLEDPin PB_0

Serial pc(USBTX,USBRX);
Timer timer;
DigitalIn inputPIR(pirPin);
DigitalIn userButton(userButtonPin);
DigitalOut UserLED(UserLEDPin);
Timer t;

bool movement = false;
bool hasPrinted = false;

void pirHigh();
void serialTest();
void setLedWithMovement();

int main() {
  // serialTest();
  // inputPIR.rise(&pirHigh);
  t.start();
  timer.start();
  setLedWithMovement();
  while(1){
      //printf("%f\n",t.read());

      setLedWithMovement();

      // Periodically sends the updated status of whether there is a person there or not
      if (timer.read() > 1.0) {
        printf("%d\n", movement);
        timer.reset();
      }

      if (inputPIR.read() == 1) {
        t.reset();
        //printf("There is movement!\n");
        movement = true;
        hasPrinted = false;
      }
      else if (t.read() > 20.0 && !hasPrinted) {
        movement = false;
        hasPrinted = true;
        //printf("They probably aren't here anymore\n");
      }
  }
  return 0;
}

// void pirHigh(){
//   hasPrinted = false;
//   t.reset();
//   printf("There is movement!\n");
// }

void setLedWithMovement(){
  if (movement)
    UserLED.write(1);
  else
    UserLED.write(0);
}


void serialTest() {
  timer.start();
  while (1) {
    if (timer.read() > 5.0) {
      pc.printf("hello\n");
      timer.reset();
    }
  }
}
