# Makefile para el proyecto "Cut the Rope" versión propia
# Autores: Eber Omar Garza Fuentes, Fatima Getsemani Lopez Plascencia.
# Fecha: 2025-05-29

# Directorios de código fuente y binarios
SRC_DIR := src
BIN_DIR := bin
INCLUDE_DIR := include

# Librerías necesarias para el proyecto (SFML y Box2D)
SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d

# Archivos fuente y ejecutables
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
EXE_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.exe,$(CPP_FILES))

# Compilación de cada archivo fuente a ejecutable
$(BIN_DIR)/%.exe: $(SRC_DIR)/%.cpp
	@echo Compilando $< para Cut the Rope...
	g++ $< -o $@ $(SFML) -I$(INCLUDE_DIR)

# Compilar todo el proyecto
all: $(EXE_FILES)
	@echo "Compilación completa de Cut the Rope (versión Capibara)"

# Ejecutar un ejecutable específico (ejemplo: make run-nivel1)
run-%: $(BIN_DIR)/%.exe
	@echo Ejecutando $< ...
	./$<

# Limpiar binarios generados
clean:
	@echo Limpiando ejecutables de Cut the Rope...
	del /Q $(BIN_DIR)\*.exe 2>nul || true

.PHONY: all clean run-%
