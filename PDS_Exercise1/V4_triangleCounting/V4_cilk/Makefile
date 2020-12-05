CC=gcc
CFLAGS = -O2 -fPIC -m64 -Wall  -lm -lcilkrts -fcilkplus

default: all

V4_triangleCount_Cilk: V4_triangleCount_Cilk.c
	$(CC) $(CFLAGS) -o $@ $^ mmio.c

.PHONY: clean

all: 	V4_triangleCount_Cilk

test: V4_triangleCount_Cilk
	@printf "\n** Testing V4_triangleCount_Cilk\n\n"
	./V4_triangleCount_Cilk s12.mtx 
	./V4_triangleCount_Cilk belgium_osm.mtx
	./V4_triangleCount_Cilk com-Youtube.mtx
	./V4_triangleCount_Cilk mycielskian13.mtx
	./V4_triangleCount_Cilk dblp-2010.mtx
	./V4_triangleCount_Cilk NACA0015.mtx

clean:
	rm -f V4_triangleCount_Cilk
