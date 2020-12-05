CC=gcc
CFLAGS = -O3 -pthread

default: all

V4_triangleCount_Pthreads: V4_triangleCount_Pthreads.c
	$(CC) $(CFLAGS) -o $@ $^ mmio.c

.PHONY: clean

all: 	V4_triangleCount_Pthreads

test: V4_triangleCount_Pthreads
	@printf "\n** Testing V4_triangleCount_Pthreads\n\n"
	./V4_triangleCount_Pthreads s12.mtx
	./V4_triangleCount_Pthreads belgium_osm.mtx
	./V4_triangleCount_Pthreads com-Youtube.mtx
	./V4_triangleCount_Pthreads mycielskian13.mtx
	./V4_triangleCount_Pthreads dblp-2010.mtx
	./V4_triangleCount_Pthreads NACA0015.mtx

clean:
	rm -f V4_triangleCount_Pthreads
