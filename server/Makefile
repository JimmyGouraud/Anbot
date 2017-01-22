
CXXFLAGS = -O4 -Wdeprecated-declarations
CPPFLAGS = -Iinclude/

CC = g++
LDFLAGS = -Wall -O3
LIBS = -lcurl -lgumbo

EXEC = main
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)


all: $(EXEC)

main: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
	rm -rf src/*.o

%.o: %.cpp
	$(CC) -o $@ -c $< $(CXXFLAGS) $(CPPFLAGS)

clean:
	rm -rf $(EXEC)
	rm -rf cookie.txt
	rm -rf offers.php
