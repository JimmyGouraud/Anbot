##############################
# EXAMPLE 2                  #
# created by T.DESCOMBES     #
#                    2015    #
##############################

NAVAJO_PRECOMPILER_EXEC = ../../bin/navajoPrecompiler


LIB_DIR      = lib
CXX 	=  g++
LIBS       = -lnavajo -L../../$(LIB_DIR) -lz -lssl -lcrypto -pthread
DEFS            =  -DLINUX -Wall -Wno-unused -fexceptions -fPIC -D_REENTRANT
CXXFLAGS        =  -O4  -Wdeprecated-declarations


CPPFLAGS	= -I. \
                  -I$(LIBSSL_DIR)/include \
		  -I../../include         \
                  -I../../MPFDParser-1.1.1
LD		=  g++

LDFLAGS        =  -Wall -Wno-unused -O3   

EXAMPLE_NAME     = example

EXAMPLE_OBJS = \
		  example.o


#######################
# DEPENDENCE'S RULES  #
#######################

%.o: %.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS) $(DEFS) 

all: $(EXAMPLE_NAME)

$(EXAMPLE_NAME): $(EXAMPLE_OBJS) $(LIB_STATIC_NAME)
	rm -f $@
	$(LD) $(LDFLAGS) -o $@ $(EXAMPLE_OBJS) $(LIB_STATIC_NAME) $(LIBS) 

clean:
	@rm -f example
	@for i in $(EXAMPLE_OBJS); do  rm -f $$i ; done






