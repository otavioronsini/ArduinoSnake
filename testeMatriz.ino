#include <LedControl.h>

#define PINO_DIN 12
#define PINO_CS  11
#define PINO_CLK 10

LedControl lc = LedControl(PINO_DIN, PINO_CLK, PINO_CS, 4);

void setup() {
  for (int i = 0; i < 4; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 15);
    lc.clearDisplay(i);
  }

  for (int i = 0; i < 4; i++) {
    for (int lin = 0; lin < 8; lin++) {
      for (int col = 0; col < 8; col++) {
        lc.setLed(i, lin, col, true);
      }
    }
  }
}

void loop() {
}
