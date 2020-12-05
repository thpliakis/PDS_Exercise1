CC=gcc
CFLAGS = -O3

default: all

V4_triangleCount: V4_triangleCount.c
	$(CC) $(CFLAGS) -o $@ $^ mmio.c

.PHONY: clean

all: 	V4_triangleCount

test: V4_triangleCount
	@printf "\n** Testing V4_triangleCount\n\n"
	./V4_triangleCount s12.mtx
	./V4_triangleCount belgium_osm.mtx
	./V4_triangleCount com-Youtube.mtx
	./V4_triangleCount mycielskian13.mtx
	./V4_triangleCount dblp-2010.mtx
	./V4_triangleCount NACA0015.mtx
clean:
	rm -f V4_triangleCount
