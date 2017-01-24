#include "hal.h"

#include "typedefs.h"
#include "serialprintf.h"

#include <stdlib.h>

uint8_t get_char(void) {
  uint8_t car;

  chnReadTimeout(&SD2, &car, 1, TIME_INFINITE);

  return (car);
}

void get_int(char* message, uint32_t* pval) {
#define MAX_CHARS_INT 10

  int nb_cars = 0;
  char string[MAX_CHARS_INT + 1]; //10 max
  int end = 0;
  uint8_t car;
  //uint32_t err;

  serialprintf(message);

  while (!end) {

    chnReadTimeout(&SD2, &car, 1, TIME_INFINITE);

    if ((car >= '0') && (car <= '9')) {
      if (nb_cars == MAX_CHARS_INT) {
        serialprintf("%c", 0x8); // backspace
        nb_cars--;
      }
      serialprintf("%c", car);
      string[nb_cars] = car;

      nb_cars++;
    }

    if (car == 0x8) // backspace
        {
      if (nb_cars > 0) {
        nb_cars--;
        serialprintf("%c %c", car, car);
      }
    }

    /* if CR, end of input */
    if (car == 0xD) {
      serialprintf("%c", car);
      serialprintf("\r\n");
      string[nb_cars] = 0; // end of string

      end = 1;
    }
  }

  /* convert to integer */
  *pval = atoi(string);

}

void get_hex(char* message, uint8_t* pval, uint32_t byte_size) {
#define MAX_HEX 32

  uint32_t nb_cars = 0;
  char string[MAX_HEX + 1]; //32 hex digit max -> 16 data bytes
  int end = 0;
  uint8_t car;
//	uint32_t err;
  int i;
  uint32_t MAX_chars = MAX_HEX;

  serialprintf("%s", message);

  if (byte_size * 2 < MAX_HEX) {
    MAX_chars = byte_size * 2;
  }
  else {
    MAX_chars = MAX_HEX;
  }

  while (!end) {

    chnReadTimeout(&SD2, &car, 1, TIME_INFINITE);

    if (((car >= '0') && (car <= '9')) || ((car >= 'A') && (car <= 'F'))
        || ((car >= 'a') && (car <= 'f'))) {
      if (nb_cars == MAX_chars) {
        printf("%c", 0x8); // backspace
        nb_cars--;
      }
      printf("%c", car);
      string[nb_cars] = car;

      nb_cars++;
    }

    if (car == 0x8) // backspace
        {
      if (nb_cars > 0) {
        nb_cars--;
        printf("%c %c", car, car);
      }
    }

    /* if CR, end of input */
    if (car == 0xD) {
      serialprintf("%c", car);
      serialprintf("\r\n");
      string[nb_cars] = 0; // end of string

      end = 1;
    }
  }

  /* clear end of 'string' */
  for (i = nb_cars; i < MAX_HEX; i++) {
    string[i] = '0';
  }

  /* convert to integer */
  for (i = 0; i < (int)byte_size; i++) {
	uint32_t digit_val = 0;
    /* MSB */
	char digit = string[2 * i];
    if ((digit >= '0') && (digit <= '9')) {
      digit_val = digit - '0';
    }
    if ((digit >= 'A') && (digit <= 'F')) {
      digit_val = digit - 'A' + 10;
    }
    if ((digit >= 'a') && (digit <= 'f')) {
      digit_val = digit - 'a' + 10;
    }
    uint32_t MSB_val = digit_val;

    /* LSB */
    digit = string[2 * i + 1];
    if ((digit >= '0') && (digit <= '9')) {
      digit_val = digit - '0';
    }
    if ((digit >= 'A') && (digit <= 'F')) {
      digit_val = digit - 'A' + 10;
    }
    if ((digit >= 'a') && (digit <= 'f')) {
      digit_val = digit - 'a' + 10;
    }
    uint32_t LSB_val = digit_val;

    pval[i] = MSB_val * 16 + LSB_val;
  }

}

/**
 * @brief   get a string
 * @details Return the next string in the stream before the \n
 *
 * @param[in]  message information message displayed in the steam
 * @param[out] pval string in the stream
 *
 * @api
 */
void get_string(char* message, char* pval, uint32_t ms) {
#define MAX_CHARS_STRING 30

  int nb_cars = 0;
  int end = 0;
  uint8_t car;
  //uint32_t err;

  serialprintf(message);

  while (!end) {

    size_t csize = chnReadTimeout(&SD2, &car, 1, ms);

    if (!csize) {
      pval[nb_cars] = 0; // end of string
      return;
    }

    if (car == 0x8) // backspace
        {
      if (nb_cars > 0) {
        nb_cars--;
        serialprintf("%c %c", car, car);
      }
    }
    /* if CR, end of input */
    else if ((car == 0xD)) {
      serialprintf("%c", car);
      serialprintf("\r\n");
      pval[nb_cars] = 0; // end of string

      end = 1;
    }
    /* ignore the LF */
    else if ((car == 0xA)) {
    }
    else {
      if (nb_cars == MAX_CHARS_STRING) {
        serialprintf("%c", 0x8); // backspace
        nb_cars--;
      }
      serialprintf("%c", car);
      pval[nb_cars] = car;

      nb_cars++;
    }
  }
}
