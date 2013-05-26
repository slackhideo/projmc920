libproj:
	cd src; $(MAKE)

test:
	cd tests; $(MAKE)

.PHONY: clean
clean:
	rm -f deeplearning; cd src; $(MAKE) clean; cd ../tests; $(MAKE) clean
