
.PHONY: all tests

CODEGEN_OBJS := c-codegen.o \
	 c-codegen-func.o c-asmgen.o c-codegen-expr.o c-codegen-decl.o \
	 c-codegen-stmt.o

OBJS :=  minic.y.o minic.lex.o c-tree.o main.o \
	 c-parse.o hashtab.o c-typecheck.o c-print.o \
	 hashmap.o c-symbol.o c-eval.o c-optimize.o  ${CODEGEN_OBJS}

all: mcc

mcc: $(OBJS) cmdline.o
	$(LD) -o $@ $(LDFLAGS) $(LIBS) $^ 

cmdline.c:
	$(LEX) -Pcmd -o$@ cmdline.lex 

tests:
	$(MAKE) -k -C tests all

clean:
	-rm -Rf $(OBJS)
	-rm -f minic.lex.c minic.y.c cmdline.c
	-rm -f mcc
	-rm -f *~
	-rm -f ./tests/minic.verbose.txt
	-rm -f minic.y.output minic.y.h

wc:
	-wc -l *.c *.y *.lex


main.o: cmdline.lex c-parse.h 
cmdline.o: cmdline.c
cmdline.c: cmdline.lex
c-parse.o: c-parse.h c-tree.h
minic.y: c-tree.h c-parse.h
minic.lex: minic.y.c
c-codegen.c: inst.def c-codegen-func.h
${CODEGEN_OBJS} : c-codegen-func.h

include Make.defs
include Make.rules
