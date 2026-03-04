#include "eeprom.h"
#include <avr/eeprom.h>

void ee_write_byte(uint16_t addr, uint8_t value) {
    // eeprom_update_byte comprueba si el valor ya existe antes de escribir
    eeprom_update_byte((uint8_t*)addr, value);
}

uint8_t ee_read_byte(uint16_t addr) {
    return eeprom_read_byte((uint8_t*)addr);
}

void ee_write_word(uint16_t addr, uint16_t value) {
    eeprom_update_word((uint16_t*)addr, value);
}

uint16_t ee_read_word(uint16_t addr) {
    return eeprom_read_word((uint16_t*)addr);
}

void ee_write_block(const void* src, uint16_t addr, uint16_t len) {
    eeprom_update_block(src, (void*)addr, len);
}

void ee_read_block(void* dest, uint16_t addr, uint16_t len) {
    eeprom_read_block(dest, (void*)addr, len);
}