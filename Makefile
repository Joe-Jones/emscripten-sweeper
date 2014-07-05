CC = emcc
CXX= em++
CFLAGS  = -g -O2
CXXFLAGS = -std=c++11 -O2  --bind
TARGET=mine.js

SOURCES = \
	mine.cpp \
	CanvasContext.cpp
	
OBJECTS = $(shell echo $(SOURCES) | sed -e 's,\.cpp,\.o,g')

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -O2 --bind $(OBJECTS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)

