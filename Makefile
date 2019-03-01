CFLAGS=-g -Wall

all: visunetlist

visunetlist: visunetlist.c netlist.o SVGwriter.o
	gcc -c $(CFLAGS) visunetlist.c
	gcc -o VisuNetList $(CFLAGS) visunetlist.o netlist.o SVGwriter.o

netlist.o: netlist.c
	gcc -c $(CFLAGS) netlist.c

SVGwriter.o: SVGwriter.c
	gcc -c $(CFLAGS) SVGwriter.c

clean:
	rm -rf *.o VisuNetList
