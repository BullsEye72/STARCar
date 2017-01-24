/**
 * @file    serialprintf.c
 * @brief   Mini printf-like functionality.
 *
 * @addtogroup serialprintf
 * @{
 */
#include "hal.h"

#include "serialprintf.h"

#define MAX_LENGTH 256

#define MAX_FILLER 11
#define FLOAT_PRECISION 100000

static char *long_to_string_with_divisor(char *p, long num, unsigned radix,
                                         long divisor) {
  int i;
  char *q;
  long l, ll;

  l = num;
  if (divisor == 0) {
    ll = num;
  }
  else {
    ll = divisor;
  }

  q = p + MAX_FILLER;
  do {
    i = (int)(l % radix);
    i += '0';
    if (i > '9')
      i += 'A' - '0' - 10;
    *--q = i;
    l /= radix;
  } while ((ll /= radix) != 0);

  i = (int)(p + MAX_FILLER - q);
  do
    *p++ = *q++;
  while (--i);

  return p;
}

static char *ltoa(char *p, long num, unsigned radix) {

  return long_to_string_with_divisor(p, num, radix, 0);
}

#if SERIALPRINTF_USE_FLOAT
static char *ftoa(char *p, double num)
{
  long l;
  unsigned long precision = FLOAT_PRECISION;

  l = num;
  p = long_to_string_with_divisor(p, l, 10, 0);
  *p++ = '.';
  l = (num - l) * precision;
  return long_to_string_with_divisor(p, l, 10, precision / 10);
}
#endif

/**
 * @brief   System formatted output function.
 * @details This function implements a minimal @p vprintf()-like functionality
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
 * @param[in] ap        list of parameters
 *
 * @api
 */
void serialvprintf(const char *fmt, va_list ap) {
  char *p, *s, c, filler;
  int i, precision, width;
  bool is_long, left_align;
  long l;
#if CHPRINTF_USE_FLOAT
  float f;
  char tmpbuf[2*MAX_FILLER + 1];
#else
  char tmpbuf[MAX_FILLER + 1];
#endif

  while (TRUE) {
    c = *fmt++;
    if (c == 0)
      return;
    if (c != '%') {
      chnWrite(&SD2, (uint8_t*)&c, 1);
      continue;
    }
    p = tmpbuf;
    s = tmpbuf;
    left_align = FALSE;
    if (*fmt == '-') {
      fmt++;
      left_align = TRUE;
    }
    filler = ' ';
    if ((*fmt == '.') || (*fmt == '0')) {
      fmt++;
      filler = '0';
    }
    width = 0;
    while (TRUE) {
      c = *fmt++;
      if ( (c >= '0') && (c <= '9'))
      c -= '0';
      else if (c == '*')
      c = va_arg(ap, int);
      else
      break;
      width = width * 10 + c;
    }
    precision = 0;
    if (c == '.') {
      while (TRUE) {
        c = *fmt++;
        if (c >= '0' && c <= '9')
        c -= '0';
        else if (c == '*')
        c = va_arg(ap, int);
        else
        break;
        precision *= 10;
        precision += c;
      }
    }
    /* Long modifier.*/
    if (c == 'l' || c == 'L') {
      is_long = TRUE;
      if (*fmt)
        c = *fmt++;
    }
    else
      is_long = (c >= 'A') && (c <= 'Z');

    /* Command decoding.*/
    switch (c) {
    case 'c':
      filler = ' ';
      *p++ = va_arg(ap, int);
      break;
    case 's':
      filler = ' ';
      if ((s = va_arg(ap, char *)) == 0)
        s = "(null)";
      if (precision == 0)
        precision = 32767;
      for (p = s; *p && (--precision >= 0); p++)
        ;
      break;
    case 'D':
    case 'd':
    case 'I':
    case 'i':
      if (is_long)
      l = va_arg(ap, long);
      else
      l = va_arg(ap, int);
      if (l < 0) {
        *p++ = '-';
        l = -l;
      }
      p = ltoa(p, l, 10);
      break;
#if CHPRINTF_USE_FLOAT
      case 'f':
      f = (float) va_arg(ap, double);
      if (f < 0)
      {
        *p++ = '-';
        f = -f;
      }
      p = ftoa(p, f);
      break;
#endif
    case 'X':
    case 'x':
      c = 16;
      goto unsigned_common;
    case 'U':
    case 'u':
      c = 10;
      goto unsigned_common;
    case 'O':
    case 'o':
      c = 8;
      unsigned_common:
      if (is_long)
      l = va_arg(ap, unsigned long);
      else
      l = va_arg(ap, unsigned int);
      p = ltoa(p, l, c);
      break;
    default:
      *p++ = c;
      break;
    }
    i = (int)(p - s);
    if ((width -= i) < 0)
      width = 0;
    if (left_align == FALSE)
      width = -width;
    if (width < 0) {
      if (*s == '-' && filler == '0') {
        chnWrite(&SD2, (uint8_t*)s++, 1);
        i--;
      }
      do
        chnWrite(&SD2, (uint8_t*)&filler, 1);
      while (++width != 0);
    }
    while (--i >= 0)
      chnWrite(&SD2, (uint8_t*)s++, 1);

    while (width) {
      chnWrite(&SD2, (uint8_t*)&filler, 1);
      width--;
    }
  }
}

void serialdisplay_word(vuint32_t word) {
  serialprintf("%08x", word);
  osalThreadSleepMilliseconds(100);
}

void serialdisplay_array(uint8_t* buffer, int byte_count) {
  int i;
  uint8_t* buf_pt = (uint8_t*)buffer;

  for (i = 0; i < byte_count; i++) {
    serialprintf("%02x", buf_pt[i]);
    if (i % 15 == 1)
      serialprintf(" ");
  }

  serialprintf("\r\n", buf_pt[i]);
  osalThreadSleepMilliseconds(100);
}

#if 0
void serialprint_string( char * string )
{
  int cnt = 0;
  int i = 0;

  for(i=0; i<MAX_LENGTH; i++)
  {
    if(string[i] == 0)
    {
      cnt = i;
      // exit the 'for' loop
      break;
    }
  }

  if(cnt!=0)
  {
    chnWrite(&SD2, (uint8_t*)string, cnt);
  }
  else
  {
    // either we didn't found the end of string char before the MAX_LENGTH, or the string was empty
    //--> do not display anything
  }
}
#endif

void display_buf(char* cmt, uint8_t* buf, uint32_t size) {
  //serialprint_string(cmt);
  printf(cmt);
  serialdisplay_array(buf, (int)size);
}

/** @} */
