# Makefile para compilar el proyecto Cut the Capibara.
# Asegúrate de tener instalado MinGW y SFML en tu sistema.
# Este Makefile está diseñado para ser usado en un entorno de Windows con MSYS2.

# Directorios
SRC_DIR := src
INCLUDE_DIR := include
BIN_DIR := bin

# Archivos fuente y ejecutable
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
EXE := $(BIN_DIR)/game.exe

# Compilador y flags
CXX := g++
CXXFLAGS := -std=c++17 -I$(INCLUDE_DIR) -IC:/msys64/mingw64/include -g
LDFLAGS := -LC:/msys64/mingw64/lib -lsfml-graphics -lsfml-window -lsfml-system

# Regla principal
all: $(EXE)

$(EXE): $(SRC_FILES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_DIR):
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)

run: all
	./$(EXE)

clean:
	del /Q $(BIN_DIR)\*.exe 2>nul || exit 0

.PHONY: all run clean
