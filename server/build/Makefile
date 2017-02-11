
CXXFLAGS = -O4 -Wdeprecated-declarations
CPPFLAGS = -I../include/

CXX 	= g++
LDFLAGS = -Wall -O3
LIBS 	= -lcurl -lgumbo
DEFS 	=  -DLINUX -Wall -Wno-unused -fexceptions -fPIC -D_REENTRANT

EXEC = main
SRC = $(wildcard ../src/*.cpp)
OBJ = $(SRC:.cpp=.o)




#######################
# DEPENDENCE'S RULES  #
#######################.

%.o: %.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS) $(DEFS) 

all: $(EXEC)

main: $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)
	rm -rf ../src/*.o

clean:
	rm -rf $(EXEC)
	rm -rf *.php
