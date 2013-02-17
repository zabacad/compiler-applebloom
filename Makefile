##  Makefile

##  Ian Shearin
##  CS 480




##  Global options
CCFLAGS = -Wall
LDFLAGS = 


##  Files
CFILES = main.c buffer.c lexer.c parser.c token.c tree.c
OBJFILES = $(addsuffix .o, $(basename $(CFILES)))
INFILES = stutest-parse00.in
OUTFILES = $(addsuffix .out, $(basename $(INFILES)))


##  Commands
CC = icc -c
LD = icc
RM = rm -f


##  Specials
.DEFAULT: compiler
.PHONY: clean clean-test clean-obj clean-all




##  Rules
# Build
compiler: $(OBJFILES)
	$(LD) -o $@ $(OBJFILES) $(LDFLAGS)

# *.c -> *.o as needed
%.o: %.c
	$(CC) -o $@ $< $(CCFLAGS)


# Clean
clean: clean-all

clean-test:
	-$(RM) $(OUTFILES)
	-$(RM) stutest.out

clean-obj:
	-$(RM) $(OBJFILES)

clean-all: clean-obj clean-test
	-$(RM) compiler


# Test
stutest.out: compiler $(OUTFILES)
	cat $(OUTFILES) > stutest.out

# *.in -> *.out as needed
%.out: %.in
	echo | cat $< -
	-./compiler --parse < $< > $@
	echo | cat $@ -

proftest.out: compiler
	cat $(PROFTEST)
	-./compiler --lex < $(PROFTEST) > proftest.out
	cat proftest.out
	echo
