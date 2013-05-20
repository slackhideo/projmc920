libproj:
	cd src; $(MAKE)

test:
	cd tests; $(MAKE)

.PHONY: clean
clean:
	cd src; $(MAKE) clean; cd ../tests; $(MAKE) clean
