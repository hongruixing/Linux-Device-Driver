SUBDIRS = block block/pci/ char misc

all: subdirs

subdirs:
	@	for n in $(SUBDIRS); do \
	 		for k in `ls -d $$n/*`; do \
				if test  -f $$k/Makefile ; then \
	  				$(MAKE) -C $$k || exit 1; \
				fi;\
			done; \
		done


clean:
	@	for n in $(SUBDIRS); do \
	 		for k in `ls -d $$n/*`; do \
				if test  -f $$k/Makefile ; then \
	  				$(MAKE) -C $$k clean || exit 1; \
				fi;\
		 	done; \
		done
