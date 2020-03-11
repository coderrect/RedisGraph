CFLAGS = -D_GNU_SOURCE -std=gnu99 -fopenmp -g -ggdb -O3

GRAPHBLAS=../deps/GraphBLAS/build/libgraphblas.a

all:
	$(CC) $(CFLAGS) -o graph_race graph_race.c $(GRAPHBLAS) -lm

clean:
	rm graph_race
