#include <mbed.h>

#define pirPin PF_13
#define userButtonPin PC_13

Serial pc(USBTX,USBRX);
Timer timer;
DigitalIn inputPIR(pirPin);
DigitalIn userButton(userButtonPin);
Timer t;

bool movement;
bool hasPrinted = false;

void pirHigh();
void serialTest();

int main() {
  // serialTest();
  // inputPIR.rise(&pirHigh);
  t.start();
  timer.start();
  while(1){
      //printf("%f\n",t.read());

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

void sendMessage(){

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
