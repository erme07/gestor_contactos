# Nombre del ejecutable
EXECUTABLE=gestor

# Directorios
SRC_DIR=./src
INCLUDE_DIR=./include
BUILD_DIR=./build
RES_DIR=./res

# Archivos de origen
SRC=$(SRC_DIR)/main.c $(SRC_DIR)/menu.c $(SRC_DIR)/consola.c $(SRC_DIR)/contact.c $(SRC_DIR)/list.c $(SRC_DIR)/draw.c

# Archivos objeto
OBJ=$(BUILD_DIR)/main.o $(BUILD_DIR)/menu.o $(BUILD_DIR)/consola.o $(BUILD_DIR)/contact.o $(BUILD_DIR)/list.o $(BUILD_DIR)/draw.o $(BUILD_DIR)/resource.o

# Compilador
CC=gcc

# Opciones de compilación
CFLAGS=-I$(INCLUDE_DIR) -Wall

# Objetivo por defecto
all: create_dirs $(EXECUTABLE)

# Enlazar ejecutable
$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

# Compilar archivos fuente a archivos objeto
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(INCLUDE_DIR)/menu.h $(INCLUDE_DIR)/consola.h $(INCLUDE_DIR)/contactlist.h | create_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/menu.o: $(SRC_DIR)/menu.c $(INCLUDE_DIR)/menu.h $(INCLUDE_DIR)/consola.h | create_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/consola.o: $(SRC_DIR)/consola.c $(INCLUDE_DIR)/consola.h $(INCLUDE_DIR)/menu.h | create_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/contact.o: $(SRC_DIR)/contact.c $(INCLUDE_DIR)/contactlist.h $(INCLUDE_DIR)/consola.h $(INCLUDE_DIR)/menu.h $(INCLUDE_DIR)/draw.h | create_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/list.o: $(SRC_DIR)/list.c $(INCLUDE_DIR)/contactlist.h $(INCLUDE_DIR)/consola.h $(INCLUDE_DIR)/menu.h $(INCLUDE_DIR)/draw.h | create_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/draw.o: $(SRC_DIR)/draw.c $(INCLUDE_DIR)/draw.h $(INCLUDE_DIR)/consola.h | create_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/resource.o: $(RES_DIR)/resource.rc | create_dirs
	windres $< -O coff -o $@

# Crear directorios necesarios
create_dirs:
	mkdir -p $(BUILD_DIR)

# Limpiar archivos generados
clean:
	rm -f $(BUILD_DIR)/*.o $(EXECUTABLE)

.PHONY: all clean create_dirs