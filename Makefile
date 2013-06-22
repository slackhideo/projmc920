libproj:
	cd src; $(MAKE)

test:
	cd tests; $(MAKE)

run:
	./deeplearning

.PHONY: clean
clean:
	rm -f deeplearning; cd src; $(MAKE) clean; cd ../tests; $(MAKE) clean
