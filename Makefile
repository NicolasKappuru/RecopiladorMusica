# Carpetas donde buscar .cpp
SRC_DIRS := Controlador ModeloDAO_Objetos ModeloDAO_Interfaces ModeloDAO_LinkArb Modelo_Estatico Modelo_Estructuras Modelo_EstructuraNodos Modelo_Singleton_Arboles Modelo_PosicionesLibres VistaConsola Controlador_Mediator Controlador_Consultas Controlador_Link

# Archivos fuente
SOURCES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))

# Objetos en build/obj/
OBJECTS := $(patsubst %.cpp, build/obj/%.o, $(SOURCES))

# Compilador
CXX := g++
CXXFLAGS := -g -Wall -std=c++17 -I.

# Ejecutable final
TARGET := build/main.exe

# Regla principal
all: $(TARGET)

# Link final
$(TARGET): $(OBJECTS)
	if not exist build mkdir build
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar cada .cpp -> .o (asegura subcarpetas)
build/obj/%.o: %.cpp
	if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar todo
clean:
	rd /s /q build
