//
//  How to access GPIO registers from C-code on the Raspberry-Pi
//  Example program
//  15-January-2012
//  Dom and Gert
//


// Access from ARM Running Linux

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "RPiGPIO.h"

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int  mem_fd;
char *gpio_mem, *gpio_map;
char *spi0_mem, *spi0_map;

// I/O access
volatile unsigned *gpio;

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0
#define GPIO_GET *(gpio+13) // read   bits

#define	MAX_PORTNUM	25

char valid_port[] = {
  1,1,0,0,
  0,0,0,1,
  1,1,1,1,
  0,0,1,1,
  0,1,1,0,
  0,1,1,1,
  1,1
};

void input_gpio(int pin)
{
  *(gpio+((pin)/10)) &= ~(7<<(((pin)%10)*3));
}

void output_gpio(int pin)
{
  input_gpio(pin);
  *(gpio+((pin)/10)) |=  (1<<(((pin)%10)*3));
}

void set_gpio_alternative(int pin, int alt)
{
  input_gpio(pin);
  *(gpio+(pin/10)) |= (((alt)<=3?(alt)+4:(alt)==4?3:2)<<(((pin)%10)*3));
}

int port_avail(int port)
{
	if ((port < 0) || (port > MAX_PORTNUM))
		return (0);
	return ((int)valid_port[port]);
}

int gpio_read(int port)
{
	if (!port_avail(port))
		return(0);
	return( (GPIO_GET & (1<<port)) ? 1 : 0);
}

void gpio_write(int port, int data)
{
	if (!port_avail(port))
		return;
	if (data == 0)
		GPIO_CLR = 1<<port;
	else	GPIO_SET = 1<<port;
}

//
// Set up a memory regions to access GPIO
//
void setup_io()
{
  static int initialized = 0;
  if(initialized) return;
  initialized = 1;

  /* open /dev/mem */
  if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0)
  {
    printf("can't open /dev/mem \n");
    exit (-1);
  }

  /* mmap GPIO */

  // Allocate MAP block
  if ((gpio_mem = (char *)malloc(BLOCK_SIZE + (PAGE_SIZE-1))) == NULL)
  {
    printf("allocation error \n");
    exit (-1);
  }

  // Make sure pointer is on 4K boundary
  if ((unsigned long)gpio_mem % PAGE_SIZE)
   gpio_mem += PAGE_SIZE - ((unsigned long)gpio_mem % PAGE_SIZE);

  // Now map it
  gpio_map = (char *)mmap(
    (caddr_t)gpio_mem,
    BLOCK_SIZE,
    PROT_READ|PROT_WRITE,
    MAP_SHARED|MAP_FIXED,
    mem_fd,
    GPIO_BASE
  );

  if ((long)gpio_map < 0)
  {
    printf("mmap error %d\n", (int)gpio_map);
    exit (-1);
  }

  // Always use volatile pointer!
  gpio = (volatile unsigned *)gpio_map;

} // setup_io
