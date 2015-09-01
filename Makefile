CC=g++
CFLAGS=-c -Wall -O3 -std=c++11
LDFLAGS=
SOURCES=array.cpp
OBJECTS=$(SOURCES:.cpp=.o)
ASM=$(SOURCES:.cpp=.s)
EXECUTABLE=arraytest

all: $(SOURCES) $(EXECUTABLE) $(ASM)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.cpp.s:
	$(CC) -S $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf *.o *.s $(EXECUTABLE)
