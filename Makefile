CC=x86_64-w64-mingw32-g++
CFLAGS=-std=c++17
LIBS=-lgdi32 -luser32
SRC=src/main.cpp
OBJ=$(SRC:.cpp=.o)
TARGET=calculator.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
