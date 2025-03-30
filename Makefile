C_COMPILER := clang
C_COMPILER_FLAGS := -O0

sparsik: sparsik.o
	${C_COMPILER} ${C_COMPILER_FLAGS} "${<}" -o "${@}" 

sparsik.o: sparsik.c
	${C_COMPILER} ${C_COMPILER_FLAGS} -c "${<}" 

