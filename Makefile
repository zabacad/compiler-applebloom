##  Makefile

##  Ian Shearin
##  CS 480




##  Global options
CCFLAGS = -Wall
LDFLAGS = 


##  Files
CFILES = main.c lexer.c
OBJFILES = $(addsuffix .o, $(basename $(CFILES)))


##  Commands
CC = icc -c
LD = icc
RM = rm -f


##  Specials
.DEFAULT: compiler
.PHONY: compiler clean




##  Rules
# Build
compiler: $(OBJFILES)
	$(LD) -o $@ $(OBJFILES) $(LDFLAGS)

# *.c -> *.o as needed
%.o: %.c
	$(CC) -o $@ $< $(CCFLAGS)


#Clean
clean:
	-$(RM) $(OBJFILES)

clean-all: clean
	-$(RM) compiler


# Test
stutest.out:

proftest.out:
