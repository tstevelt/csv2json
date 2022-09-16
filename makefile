
PROG = csv2json
LIB = csv2json.a
PRG = /usr/local/bin/$(PROG)

FILES = \
	$(LIB)(csv2json.o)	\
	$(LIB)(getargs.o)	\
	$(LIB)(gettoks.o)	\
	$(LIB)(gettypes.o)

.SILENT:

$(PRG): $(LIB) $(XLIB)
	echo "using gcc to load $(PRG)"
	gcc -o $(PRG) $(LIB) $(XLIB)

$(LIB): $(FILES)

$(FILES): csv2json.h

clean:
	rm -f $(LIB)
	rm -f *.json

all:
	make clean
	make

.PRECIOUS: $(LIB)

