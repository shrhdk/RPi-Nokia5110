#include "RPiSPI.h"

int object_validity_;
int last_error_;
int file_descriptor_;
uint8_t mode_;
uint8_t bits_per_word_;
uint32_t bits_per_sec_;
uint16_t delay_;

/**
 * Open spidev.
 * @param device File name of spidev, such as "/dev/spidev0.0".
 * @param mode SPI mode.
 * @param bits_per_word Bits per word, such as 8.
 * @param bits_per_sec Bits per second, such as 500000.
 * @param delay Microseconds to delay after transfer before (optionally) changing the chipselect status, then starting the next transfer or completing this spi_message.
 */

void RPiSPI_Open(const char* device, uint8_t mode, uint8_t bits_per_word, uint32_t bits_per_sec, uint8_t delay)
{
  file_descriptor_ = open(device, O_RDWR);

  object_validity_ = (file_descriptor_ != -1);
  if(!object_validity_)
    last_error_ = RPISPI_OPEN_FAILED;
  else
    last_error_ = 0;

  RPiSPI_set_mode(mode);
  RPiSPI_set_bits_per_word(bits_per_word);
  RPiSPI_set_bits_per_sec(bits_per_sec);
  RPiSPI_set_delay(delay);
}

/**
 * Close spidev.
 */

void RPiSPI_Close(void)
{
  close(file_descriptor_);
}

/**
 * Check that spidev is opened.
 * @return true: object is valid. It is readied for transfer. / false: object is invalid.
 */

int RPiSPI_IsOpen()
{
  return object_validity_;
}

/**
 * Getter for last error code.
 * @return Last error code defined in SpiDev::Errors.
 */

int RPiSPI_get_last_error(void)
{
  return last_error_;
}

/**
 * Transfer function.
 * @param transmit_buffer Pointer to transmit buffer.
 * @param receive_buffer Pointer to receive buffer.
 * @param length Buffer length (In words).
 * @return Return -1 if transfer failed.
 */

int RPiSPI_Transfer(const void *transmit_buffer, void *receive_buffer, size_t length)
{
  struct spi_ioc_transfer tr;
  tr.tx_buf = (unsigned long)transmit_buffer;
  tr.rx_buf = (unsigned long)receive_buffer;
  tr.len = length;
  tr.delay_usecs = delay_;
  tr.speed_hz = bits_per_sec_;
  tr.bits_per_word = bits_per_word_;

  return ioctl(file_descriptor_, SPI_IOC_MESSAGE(1), &tr);
}

/**
 * Getter for SPI mode.
 * @return SPI mode.
 */

uint8_t RPiSPI_get_mode(void)
{
  int ret = ioctl(file_descriptor_, SPI_IOC_RD_MODE, &mode_);
  if(ret == -1) last_error_ = RPISPI_GET_MODE_FAILED;
  return (ret != -1) ? mode_ : -1;
}

/**
 * Setter for SPI mode.
 * @param mode SPI mode.
 * @return Return -1 if set failed.
 */

int RPiSPI_set_mode(uint8_t mode)
{
  mode_ = mode;
  int ret = ioctl(file_descriptor_, SPI_IOC_WR_MODE, &mode_);
  if(ret == -1) last_error_ = RPISPI_SET_MODE_FAILED;
  return ret;
}

/**
 * Getter for bits per word.
 * @return Bits per word.
 */

uint8_t RPiSPI_get_bits_per_word(void)
{
  int ret = ioctl(file_descriptor_, SPI_IOC_RD_BITS_PER_WORD, &bits_per_word_);
  if(ret == -1) last_error_ = RPISPI_GET_BITS_FAILED;
  return (ret != -1) ? bits_per_word_ : -1;
}

/**
 * Setter for bits per word.
 * @param bits_per_word Bits per word.
 * @return Return -1 if set failed.
 */

int RPiSPI_set_bits_per_word(uint8_t bits_per_word)
{
  bits_per_word_ = bits_per_word;
  int ret = ioctl(file_descriptor_, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word_);
  if(ret == -1) last_error_ = RPISPI_SET_BITS_FAILED;
  return ret;
}

/**
 * Getter for bits per sec.
 * @return Bits per sec.
 */

uint32_t RPiSPI_get_bits_per_sec(void)
{
  int ret = ioctl(file_descriptor_, SPI_IOC_RD_MAX_SPEED_HZ, &bits_per_sec_);
  if(ret == -1) last_error_ = RPISPI_GET_SPEED_FAILED;
  return (ret != -1) ? bits_per_sec_ : -1;
}

/**
 * Setter for bits per sec.
 * @param bits_per_sec Bits per sec.
 * @return Return -1 if set failed.
 */

int RPiSPI_set_bits_per_sec(uint32_t bits_per_sec)
{
  bits_per_sec_ = bits_per_sec;
  int ret = ioctl(file_descriptor_, SPI_IOC_WR_MAX_SPEED_HZ, &bits_per_sec_);
  if(ret == -1) last_error_ = RPISPI_SET_SPEED_FAILED;
  return ret;
}

/**
 * Getter for delay.
 * @return Delay.
 */

uint16_t RPiSPI_get_delay(void)
{
  if(0 <= delay_)
  {
    return delay_;
  }
  else
  {
    last_error_ = RPISPI_GET_DELAY_FAILED;
    return -1;
  }
}

/**
 * Setter for delay.
 * @param delay Microseconds to delay after transfer before (optionally) changing the chipselect status.
 * @return Return -1 if set failed.
 */

uint16_t RPiSPI_set_delay(uint16_t delay)
{
  if(0 <= delay)
  {
    return (delay_ = delay);
  }
  else
  {
    last_error_ = RPISPI_SET_DELAY_FAILED;
    return -1;
  }
}
