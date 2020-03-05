CFLAGS = -D_GNU_SOURCE -std=gnu99 -fopenmp -g -ggdb -O3

GRAPHBLAS=../deps/GraphBLAS/build/libgraphblas.a

all:
	$(CC) $(CFLAGS) -o hang hang.c $(GRAPHBLAS) -lm

clean:
	rm hang
