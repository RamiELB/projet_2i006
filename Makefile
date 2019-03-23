CFLAGS=-g -Wall

all: visunetlist

visunetlist: visunetlist.c netlist.o SVGwriter.o
	gcc -c $(CFLAGS) visunetlist.c
	gcc -o VisuNetList $(CFLAGS) SVGwriter.o netlist.o visunetlist.o  

netlist.o: netlist.c
	gcc -c $(CFLAGS) netlist.c

SVGwriter.o: SVGwriter.c
	gcc -c $(CFLAGS) SVGwriter.c

intersection.o: intersection.c
	gcc -c $(CFLAGS) intersection.c

balayage.o: balayage.c
	gcc -c $(CFLAGS) balayage.c

avl.o: avl.c
	gcc -c $(CFLAGS) avl.c

test: netlist.o intersection.o balayage.o avl.o 
	gcc -o test $(CFLAGS) netlist.o intersection.o balayage.o avl.o
	
clean:
	rm -rf *.o VisuNetList *.html Instance_Netlist/*.html Instance_Netlist/*.int
