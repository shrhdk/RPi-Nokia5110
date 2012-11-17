#ifndef RPISPI_H
#define RPISPI_H

#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define RPISPI_OPEN_FAILED        (0x01)
#define RPISPI_GET_MODE_FAILED    (0x02)
#define RPISPI_SET_MODE_FAILED    (0x03)
#define RPISPI_GET_BITS_FAILED    (0x04)
#define RPISPI_SET_BITS_FAILED    (0x05)
#define RPISPI_GET_SPEED_FAILED   (0x06)
#define RPISPI_SET_SPEED_FAILED   (0x07)
#define RPISPI_GET_DELAY_FAILED   (0x08)
#define RPISPI_SET_DELAY_FAILED   (0x09)

void RPiSPI_Open(const char* device, uint8_t mode,  uint8_t bits_per_word, uint32_t bits_per_sec,uint8_t delay);
void RPiSPI_Close(void);
int RPiSPI_IsOpen(void);
int RPiSPI_get_last_error(void);
int RPiSPI_Transfer(const void *tx, void *rx, size_t length);

/* mode_ */
uint8_t RPiSPI_get_mode(void);
int RPiSPI_set_mode(uint8_t mode);

/* bits_per_words_ */
uint8_t RPiSPI_get_bits_per_word(void);
int RPiSPI_set_bits_per_word(uint8_t bits_per_word);

/* bits_per_sec */
uint32_t RPiSPI_get_bits_per_sec(void);
int RPiSPI_set_bits_per_sec(uint32_t bits_per_sec);

/* delay_ */
uint16_t RPiSPI_get_delay(void);
uint16_t RPiSPI_set_delay(uint16_t delay);

#endif