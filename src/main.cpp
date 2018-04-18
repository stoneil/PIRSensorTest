#include <mbed.h>

#define pirPin PF_13
#define userButtonPin PC_13

InterruptIn inputPIR(pirPin);
DigitalIn userButton(userButtonPin);
Timer t;

bool movement;
bool hasPrinted = false;

void pirHigh();

int main() {
  inputPIR.rise(&pirHigh);
  t.start();

  while(1){
      //printf("%f\n",t.read());
      if (t.read() > 10.0 && !hasPrinted) {
        hasPrinted = true;
        printf("They probably aren't here anymore\n");
      }
  }
  return 0;
}

void pirHigh(){
  hasPrinted = false;
  t.reset();
  printf("There is movement!\n");
}
