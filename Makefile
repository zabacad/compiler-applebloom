##  Makefile

##  Ian Shearin
##  CS 480




##  Global options
CCFLAGS = -Wall
LDFLAGS = 


##  Files
CFILES = main.c buffer.c lexer.c
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
clean: clean-all

clean-obj:
	-$(RM) $(OBJFILES)

clean-all: clean-obj
	-$(RM) compiler


# Test
stutest.out:

proftest.out:
