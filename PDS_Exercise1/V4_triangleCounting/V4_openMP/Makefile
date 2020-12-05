CC=gcc
CFLAGS = -O2 -lm -fopenmp

default: all

V4_triangleCount_openMP: V4_triangleCount_openMP.c
	$(CC) $(CFLAGS) -o $@ $^ mmio.c

.PHONY: clean

all: 	V4_triangleCount_openMP

test: V4_triangleCount_openMP
	@printf "\n** Testing V4_triangleCount_openMP\n\n"
	./V4_triangleCount_openMP s12.mtx
	./V4_triangleCount_openMP belgium_osm.mtx
	./V4_triangleCount_openMP com-Youtube.mtx
	./V4_triangleCount_openMP mycielskian13.mtx
	./V4_triangleCount_openMP dblp-2010.mtx
	./V4_triangleCount_openMP NACA0015.mtx

clean:
	rm -f V4_triangleCount_openMP
