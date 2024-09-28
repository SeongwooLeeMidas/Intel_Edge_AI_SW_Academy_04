.EXPORT_ALL_VARIABLES:

DIRS = $(wildcard */)

all:
	for i in $(DIRS) ; do make -C $$i || exit $? ; done
clean:
	for i in $(DIRS) ; do make -C $$i clean; done

