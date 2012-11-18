#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "../src/Nokia5110.h"

#define SPIDEV      ("/dev/spidev0.0")
#define RESET_PIN   (24)
#define DC_PIN      (25)

int main(int argc, const char *argv[])
{
  Nokia5110_Initialize(SPIDEV, RESET_PIN, DC_PIN);

  Nokia5110_RPi();
  sleep(2);

  Nokia5110_DrawString(0, 0, "RPi-Nokia5110\n\n hello world");
  Nokia5110_Flush();

  return EXIT_SUCCESS;
}