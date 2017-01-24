/**
 * @file    printf.h
 * @brief   Mini printf-like functionality.
 * @details Minimal OS less printf support, using serial port. Code comes from chibiOS chprintf.c/.h module
 *
 *
 * @addtogroup printf
 * @{
 */

#ifndef SERIALPRINTF_H_
#define SERIALPRINTF_H_

#include <stdarg.h>
#include "typedefs.h"

#define printf serialprintf

/**
 * @brief   Float type support.
 */
#if !defined(CHPRINTF_USE_FLOAT) || defined(__DOXYGEN__)
#define CHPRINTF_USE_FLOAT          FALSE
#endif

extern void serialvprintf(const char *fmt, va_list ap);

/**
 * @brief   System formatted output function.
 * @details This function implements a minimal @p printf() like functionality
 *          with output on serial port.
 *          The general parameters format is: %[-][width|*][.precision|*][l|L]p.
 *          The following parameter types (p) are supported:
 *          - <b>x</b> hexadecimal integer.
 *          - <b>X</b> hexadecimal long.
 *          - <b>o</b> octal integer.
 *          - <b>O</b> octal long.
 *          - <b>d</b> decimal signed integer.
 *          - <b>D</b> decimal signed long.
 *          - <b>u</b> decimal unsigned integer.
 *          - <b>U</b> decimal unsigned long.
 *          - <b>c</b> character.
 *          - <b>s</b> string.
 *          .
 *
 * @param[in] fmt       formatting string
 *
 * @api
 */
static inline void serialprintf(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  serialvprintf(fmt, ap);
  va_end(ap);
}

/**
 * @brief   System formatted 32bits word output function.
 * @details This function displays a 32bits integer value in hexadecimal, with 8 digits on serial port.
 *
 * @param[in] word value to display
 *
 * @api
 */
extern void serialdisplay_word(uint32_t word);

/**
 * @brief   System formatted data buffer output function.
 * @details This function displays a specified number of bytes of the provided buffer array in hexadecimal (2 digits per byte)
 *
 * @param[in] buffer pointer to the data location
 * @param[in] byte_count number of bytes to dispaly (2 hex digits per bytes)
 *
 * @api
 */
extern void serialdisplay_array(uint8_t* buffer, int byte_count);

/**
 * @brief   System formatted string output function.
 * @details This function displays a text string (it displays a maximum of MAX_LENGTH chars, or stops if it finds an endofstring char (0) before)
 *
 * @param[in] string pointer to the data location
 *
 * @api
 */
extern void serialprint_string(char * string);

/**
 * @brief   System formatted data buffer output function.
 * @details This function displays a specified number of bytes of the provided buffer array in hexadecimal (2 digits per byte) with the provided comment string before
 *
 * @param[in] cmt pointer to a comment string (muts be terminated by a end_of_string '\0' character)
 * @param[in] buffer pointer to the data location
 * @param[in] byte_count number of bytes to dispaly (2 hex digits per bytes)
 *
 * @api
 */
extern void display_buf(char* cmt, uint8_t* buf, uint32_t size);

#endif /* SERIALPRINTF_H_ */
