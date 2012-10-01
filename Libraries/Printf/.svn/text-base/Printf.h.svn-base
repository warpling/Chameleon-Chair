#ifndef STREAM_PRINTF_H
#define STREAM_PRINTF_H 1

/**
 * http://www.utopiamechanicus.com/article/sprintf-arduino/ 
 * Posted on July 20, 2011 by David Pankhurst 
 **/
 
#include <Arduino.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include <stdarg.h>
 
extern void Stream_printf_progmem(Print &out, PGM_P format, ...);

#define Serial_printf(format, ...) Stream_printf_progmem(Serial, PSTR(format), ##__VA_ARGS__)
#define Stream_printf(stream, format, ...) Stream_printf_progmem(stream, PSTR(format), ##__VA_ARGS__)

#endif
 