#ifndef _SERIAL_INPUT_H_
#define _SERIAL_INPUT_H_

#include "typedefs.h"
#include "serialprintf.h"

extern uint8_t get_char(void);
extern void get_int(char* message, uint32_t* pval);
extern void get_hex(char* message, uint8_t* pval, uint32_t byte_size);
extern void get_string(char* message, char* pval, uint32_t ms);

#endif //_SERIAL_INPUT_H_
