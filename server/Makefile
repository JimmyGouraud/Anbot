
OUTPUTFILENAME = PrecompiledRepository.cc
NAVAJO_PRECOMPILER_EXEC = ext/libnavajo/bin/navajoPrecompiler

CXXFLAGS = -O4 -Wdeprecated-declarations
CPPFLAGS = -Iinclude/

CXX 	= g++
LDFLAGS = -Wall -O3
LIBS 	= -lcurl -lgumbo
DEFS 	=  -DLINUX -Wall -Wno-unused -fexceptions -fPIC -D_REENTRANT

EXEC = main
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)




#######################
# DEPENDENCE'S RULES  #
#######################.

%.o: %.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS) $(DEFS) 

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(CPPFLAGS) $(DEFS) 

all: $(EXEC)

PrecompiledRepository.o:
	@echo Generate Cpp files from HTML repository
	@rm -f $(OUTPUTFILENAME)
	@find . \( -name "*~" -o -name "*.old" -o -name "*.bak" \) -exec rm -f '{}' \;
	@$(NAVAJO_PRECOMPILER_EXEC) exampleRepository >> $(OUTPUTFILENAME) ; cd ..
	$(CXX) -c PrecompiledRepository.cc -o $@ $(CXXFLAGS) $(CPPFLAGS) $(DEFS)

main: $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)
	rm -rf src/*.o

clean:
	rm -rf $(EXEC)
	rm -rf cookie.txt
	rm -rf offers.php
