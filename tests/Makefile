include ../make.inc

# Ajusta variáveis de caminhos
INCLUDE := ../$(INCLUDE)
LIB := ../$(LIB)

.PHONY: run
run: tests
	@echo ""
	./runTests.sh

tests: $(LIB)/libproj.a testReadWrite testAdjRel testKernel testFilter testRandKernels

$(LIB)/libproj.a:
	cd ../src; $(MAKE)

testReadWrite: testReadWrite.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) \
			-o testReadWrite testReadWrite.c -lproj -lm

testAdjRel: testAdjRel.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) \
			-o testAdjRel testAdjRel.c -lproj

testKernel: testKernel.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) \
			-o testKernel testKernel.c -lproj -lm

testFilter: testFilter.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) \
			-o testFilter testFilter.c -lproj -lm

testRandKernels: testRandKernels.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) \
			-o testRandKernels testRandKernels.c -lproj -lm

poolingTest: poolingTest.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) \
			-o poolingTest poolingTest.c -lproj -lm


.PHONY: clean
clean:
	rm -f testReadWrite testAdjRel testKernel testFilter testRandKernels
	rm -f flower_out.pgm adjRel_out	kernel_out filter_out.pgm *~ \
			randKernels_out
