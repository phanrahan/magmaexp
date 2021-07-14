MAGMA=~/git/magma/
DEVICE='xc6slx9'

TESTS = count3.xdl count6.xdl count7.xdl count8.xdl count16.xdl

.PHONY: test gold clean

test: $(TESTS)

gold:
	for f in $(TESTS); do \
		cp $$f $$f.gold; \
	done

clean: 
	rm -f *.pyc *.xdl *.pcf *.bit 
	make -C build clean

%.xdl: %.py
	rm -f $*.pcf $*.xdl
	${MAGMA}/bin/magma -d ${DEVICE} -o $@ -p $*.pcf $*
	if [ -e $@.gold ] ; then \
		diff $@ $@.gold ; \
	fi

%.bit: %.xdl
	make -C build clean
	cp $*.xdl build/fpga.xdl
	cp $*.pcf build/fpga.pcf
	make -C build 
	cp build/test.bit $@
