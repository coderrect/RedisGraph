#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>
#include "../deps/GraphBLAS/Include/GraphBLAS.h"

#define ROWCOUNT 10000 // NOTE - smaller values do not cause the child to hang
#define DELETECOUNT 100

/* RedisGraph delete routine */
GrB_Info GxB_Matrix_Delete(GrB_Matrix M, GrB_Index row, GrB_Index col) {
	GrB_Matrix Z ;  // 1X1 empty matrix.
	GrB_Matrix_new(&Z, GrB_BOOL, 1, 1) ;

	GrB_Info info = GxB_Matrix_subassign(M, GrB_NULL, GrB_NULL, Z, &row, 1, &col, 1, GrB_NULL) ;

	GrB_Matrix_free(&Z);
	return info;
}

void _delete_nodes(GrB_Matrix M) {
	for(GrB_Index i = 0; i < DELETECOUNT; i++) {
		assert(GxB_Matrix_Delete(M, i, i) == GrB_SUCCESS);
	}
}

GrB_Matrix _build(void) {
	GrB_Matrix M;
	GrB_Matrix_new(&M, GrB_BOOL, ROWCOUNT, ROWCOUNT);

	for(GrB_Index i = 0; i < ROWCOUNT; i ++) {
		GrB_Matrix_setElement_BOOL(M, true, i, i);
	}

	return M;
}

int main(int argc, char **argv) {
	GrB_init(GrB_NONBLOCKING);

	// Build a diagonal matrix.
	GrB_Matrix M = _build();

	// Delete some entries from the new matrix.
	_delete_nodes(M);

	// Child does not hang if this line is uncommented.
	// GrB_wait();

	pid_t pid = fork();
	if(pid == 0) {
		// Print node count in child.
		GrB_Index n;
		GrB_Matrix_nvals(&n, M); // hangs here
		printf("number of values: %lu\n", n);
		printf("child completed\n");
	} else {
		printf("child pid: %u\n", pid);
		printf("parent completed\n");
	}

	return 0;
}

