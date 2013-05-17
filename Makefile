libproj:
	cd src; make

test:
	cd src; make test; mv test ../

.PHONY: clean
clean:
	cd src; make clean
