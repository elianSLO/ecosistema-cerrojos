#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>

void ee_write_byte(uint16_t addr, uint8_t value);

uint8_t ee_read_byte(uint16_t addr);

void ee_write_word(uint16_t addr, uint16_t value);

uint16_t ee_read_word(uint16_t addr);

void ee_write_block(const void* src, uint16_t addr, uint16_t len);

void ee_read_block(void* dest, uint16_t addr, uint16_t len);

#endif