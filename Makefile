##  Makefile

##  Ian Shearin
##  CS 480




##  Global options
CCFLAGS = -Wall
LDFLAGS = 


##  Files
CFILES = main.c buffer.c lexer.c token.c
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
	cat stutest.in
	-./compiler --lex < stutest.in > stutest.out
	cat stutest.out

proftest.out:
	cat $(PROFTEST)
	-./compiler --lex < $(PROFTEST) > proftest.out
	cat proftest.out
