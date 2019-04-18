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

graphe.o: graphe.c
	gcc -c $(CFGLAGS) graphe.c

via_cycle.o: via_cycle.c
	gcc -c $(CFGLAGS) via_cycle.c

via_naif.o: via_naif.c
	gcc -c $(CFLAGS) via_naif.c	

test: netlist.o intersection.o graphe.o
	gcc -o test $(CFLAGS) netlist.o intersection.o graphe.o

benchmarking: benchmarking.c netlist.o intersection.o balayage.o avl.o
	gcc -c $(CFLAGS) benchmarking.c
	gcc -o benchmarking $(CFLAGS) benchmarking.o netlist.o intersection.o balayage.o avl.o

visugraphe: visugraphe.c netlist.o graphe.o SVGwriter.o intersection.o
	gcc -c $(CFLAGS) visugraphe.c
	gcc -o visugraphe $(CFLAGS) visugraphe.o netlist.o graphe.o SVGwriter.o intersection.o

creationint: creationint.c netlist.o intersection.o balayage.o
	gcc -c $(CFLAGS) creationint.c
	gcc -o creationint $(CFLAGS) creationint.o netlist.o intersection.o balayage.o

visuvianaif: visuvianaif.c via_naif.o netlist.o graphe.o SVGwriter.o intersection.o
	gcc -c $(CFLAGS) visuvianaif.c
	gcc -o visuvianaif $(CFLAGS) visuvianaif.o via_naif.o netlist.o graphe.o SVGwriter.o intersection.o

testviacycle: netlist.o via_cycle.o graphe.o balayage.o intersection.o
	gcc -o testviacycle netlist.o via_cycle.o graphe.o balayage.o intersection.o

clean:
	rm -rf *.o VisuNetList *.html Instance_Netlist/*.html perf_intersec test* vgcore* .vscode/
