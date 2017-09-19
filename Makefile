SUBDIRS =  misc-modules CharDrivers USB

all: subdirs

subdirs:
	for n in $(SUBDIRS); do $(MAKE) -C $$n || exit 1; done


clean:
	for n in $(SUBDIRS); do $(MAKE) -C $$n clean; done
