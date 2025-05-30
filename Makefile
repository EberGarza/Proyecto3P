# Makefile para el proyecto "Cut the Rope" versión capibara.
# Autores: Eber Omar Garza Fuentes, Fatima Getsemani Lopez Plascencia.
# Fecha: 2025-05-29

# Directorios de código fuente y binarios
SRC_DIR := src
BIN_DIR := bin
INCLUDE_DIR := include

# Librerías necesarias para el proyecto (SFML y Box2D)
SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d

# Archivos fuente y ejecutable principal
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
MAIN_SRC := $(SRC_DIR)/00_CutTheRope.cpp
MAIN_EXE := $(BIN_DIR)/bin.exe

# Compilar el ejecutable principal enlazando los demás módulos
$(MAIN_EXE): $(SRC_FILES)
	@echo Compilando $< para Cut the Rope...
	g++ $(SRC_FILES) -o $(MAIN_EXE) $(SFML) -I$(INCLUDE_DIR)

# Compilar todo el proyecto
all: $(MAIN_EXE)
	@echo "Compilación completa de Cut the Rope (versión Capibara)"

# Ejecutar el ejecutable principal
run: $(MAIN_EXE)
	./$(MAIN_EXE)

# Limpiar binarios generados
clean:
	@echo Limpiando ejecutables de Cut the Rope...
	del /Q $(BIN_DIR)\*.exe 2>nul || true

.PHONY: all clean run
