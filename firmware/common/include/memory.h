#ifndef MEMORY_H_
#define MEMORY_H_

#define REG_INIT        0x0000
#define REG_SIZE        0x000F
#define ADDR_PTR_LOG    0x0190                      // Dirección donde guardamos el puntero actual (2 bytes)
#define LOG_START       0x01A0                      // Inicio log de eventos
#define LOG_END         0x01E0                      // Fin log de evetos (EXCLUYENTE)
#define LOG_SIZE        (LOG_END - LOG_START)

#endif