# ==============================================================================
# 1. CONFIGURACIÓN DEL HARDWARE Y PROYECTO
# ==============================================================================
# Nombre del firmware final (sin extensión)
TARGET      = SB5_v1.1

# Microcontrolador y Frecuencia de Reloj
MCU         = atmega328p
F_CPU       = 16000000UL  # 16 MHz (Ajustar si usas 8MHz interno)

# Configuración del Programador (USBasp)
PROGRAMMER  = usbasp
PORT        = usb
# -B 3 define la velocidad del reloj SCK para USBasp (valor bajo = más rápido)
BITCLOCK    = 3

# ==============================================================================
# 2. HERRAMIENTAS Y DIRECTORIOS
# ==============================================================================
CC          = avr-gcc
OBJCOPY     = avr-objcopy
SIZE        = avr-size
AVRDUDE     = avrdude

# Módulos del proyecto (Coinciden con tus carpetas físicas)
# Incluimos 'app' para cuando crees la lógica de estados
MODULES     = app hal common

# Búsqueda automática de archivos fuente (.cpp) en los módulos y la raíz
SRCS        = $(shell find $(MODULES) -name '*.cpp' 2>/dev/null) main.cpp

# Búsqueda automática de carpetas de cabeceras (-Ihal/include -Icommon/include ...)
INC_DIRS    = $(addprefix -I, $(addsuffix /include, $(MODULES)))

# Generación de la lista de objetos (.o) dentro de la carpeta 'build'
# Esto mantiene el código fuente limpio de archivos temporales
OBJS        = $(SRCS:%.cpp=build/%.o)

# ==============================================================================
# 3. FLAGS DE COMPILACIÓN Y ENLAZADO
# ==============================================================================
# -Os: Optimización para TAMAÑO (Crucial para los 32KB del ATmega328P)
# -Wall: Activa todas las advertencias para un código más robusto
# -ffunction-sections: Permite al linker eliminar funciones no utilizadas
CFLAGS      = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall $(INC_DIRS) -ffunction-sections -fdata-sections		# -Os Function inlining, si una funcion llama a otra de una libreria estandar, el compilador reemplaza directaente la llamada por el codigo de la libreria avr

# -Wl,--gc-sections: Elimina código "muerto" para ahorrar memoria Flash
LDFLAGS     = -Wl,--gc-sections

# ==============================================================================
# 4. REGLAS DE CONSTRUCCIÓN
# ==============================================================================

# Regla por defecto: Compila todo y muestra el reporte de memoria
all: build/$(TARGET).hex
	@echo "------------------------------------------------"
	@echo "Reporte de uso de memoria para $(MCU):"
	@$(SIZE) --format=avr --mcu=$(MCU) build/$(TARGET).elf
	@echo "------------------------------------------------"

# Paso 1: Generar el archivo HEX (el que se graba en el micro)
build/$(TARGET).hex: build/$(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Paso 2: Enlazar los archivos objeto (.o) para crear el archivo ELF
build/$(TARGET).elf: $(OBJS)
	@mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Paso 3: Compilar cada archivo fuente (.cpp) individualmente (Incremental)
# Crea las subcarpetas necesarias en 'build' automáticamente
build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ==============================================================================
# 5. UTILIDADES (FLASH Y LIMPIEZA)
# ==============================================================================

# Graba el firmware en el microcontrolador usando avrdude
flash: all
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -B $(BITCLOCK) -U flash:w:build/$(TARGET).hex:i

# Borra la carpeta build y todos los archivos generados
clean:
	rm -rf build/

# Declaramos las reglas que no son archivos físicos
.PHONY: all clean flash