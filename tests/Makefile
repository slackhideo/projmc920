include ../make.inc

# Ajusta variáveis de caminhos
INCLUDE := ../$(INCLUDE)
LIB := ../$(LIB)

.PHONY: run
run: tests
	@echo ""
	./runTests.sh

tests: $(LIB)/libproj.a testReadWrite testAdjRel testKernel testFilter

$(LIB)/libproj.a:
	cd ../src; $(MAKE)

testReadWrite: testReadWrite.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) \
			-o testReadWrite testReadWrite.c -lproj

testAdjRel: testAdjRel.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) \
			-o testAdjRel testAdjRel.c -lproj

testKernel: testKernel.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) \
			-o testKernel testKernel.c -lproj

testFilter: testFilter.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) \
			-o testFilter testFilter.c -lproj -lm

.PHONY: clean
clean:
	rm -f testReadWrite testAdjRel testKernel testFilter
	rm -f flower_out.pgm adjRel_out	kernel_out filter_out.pgm *~
