SUBDIRS = block char misc

all: subdirs

subdirs:
	@	for n in $(SUBDIRS); do \
	 		for k in `ls -d $$n/*`; do \
	  		$(MAKE) -C $$k || exit 1; \
			done; \
		done


clean:
	@	for n in $(SUBDIRS); do \
	 		for k in `ls -d $$n/*`; do \
	  		$(MAKE) -C $$k clean || exit 1; \
		 	done; \
		done
