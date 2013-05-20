libproj:
	cd src; $(MAKE)

test:
	cd src; $(MAKE) test; mv test ../

.PHONY: clean
clean:
	rm -f test; cd src; $(MAKE) clean;
