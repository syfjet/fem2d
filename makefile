TARGET = fem
CC = g++

CFLAGS = -Ofast

SOURCES = \
src/main.cpp \
src/reader/construction_mesh.cpp \
src/reader/read_input_file.cpp \
src/solver/geometry.cpp \
src/solver/shift.cpp \
src/solver/stress_value.cpp \
src/solver/boundary.cpp \
src/solver/linalg.cpp \
src/solver/solver.cpp \
src/paraview/out.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)




