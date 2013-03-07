##  Makefile

##  Ian Shearin
##  CS 480




##  Global options
CCFLAGS = -Wall
LDFLAGS = 


##  Files
CFILES = main.c buffer.c lexer.c map.c parser.c token.c translator.c tree.c
OBJFILES = $(addsuffix .o, $(basename $(CFILES)))
INFILES = stutest-parse00.in stutest-parse01.in stutest-parse02.in
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
	$(LD) $(LDFLAGS) -o $@ $(OBJFILES)

# *.c -> *.o as needed
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ $<


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
	echo | cat $< - > $@
	-./compiler --parse < $< >> $@
	echo | cat $@ -

proftest.out: compiler
	echo | cat $(PROFTEST) - > $@
	-./compiler --parse < $(PROFTEST) > proftest.out
	echo | cat proftest.out -
