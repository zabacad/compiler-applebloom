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

clean-test:
	-$(RM) *test*.out

clean-obj:
	-$(RM) $(OBJFILES)

clean-all: clean-obj clean-test
	-$(RM) compiler


# Test
stutest.out: compiler
	cat stutest.in
	-./compiler --lex < stutest.in > stutest.out
	cat stutest.out
	echo

proftest.out: compiler
	cat $(PROFTEST)
	-./compiler --lex < $(PROFTEST) > proftest.out
	cat proftest.out
	echo
