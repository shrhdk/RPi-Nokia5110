#ifndef RPIGPIO_H
#define RPIGPIO_H

void input_gpio(int pin);
void output_gpio(int pin);
void set_gpio_alternative(int pin, int alt);

int port_avail(int port);
int gpio_read(int port);
void gpio_write(int port, int data);
void setup_io();

#endif