#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "Nokia5110.h"

#define SPIDEV      ("/dev/spidev0.0")
#define RESET_PIN   (24)
#define DC_PIN      (25)

int main(int argc, const char *argv[])
{
  Nokia5110_Initialize(SPIDEV, RESET_PIN, DC_PIN);

  for(;;)
  {
    Nokia5110_RPi();
    sleep(1);
    Nokia5110_DrawString(0, 0, "hello world\n  yahho!");
    Nokia5110_Flush();
    sleep(1);
  }
  return EXIT_SUCCESS;
}