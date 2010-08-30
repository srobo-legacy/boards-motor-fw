ARCH = msp430x2274
CC := msp430-gcc

CFLAGS := -g -mmcu=${ARCH} -Wall -O3 -std=gnu99
CFLAGS += -include `pwd`/config.h
LDFLAGS :=

O_FILES = main.o pwm.o h-bridge.o
SUBDIRS = drivers libsric

LDFLAGS += -Ldrivers -ldrivers
LDFLAGS += -Llibsric -lsric

all: motor

include depend

motor: ${O_FILES} ${SUBDIRS}
	${CC} -o $@ ${O_FILES} ${CFLAGS} ${LDFLAGS}

drivers:
	$(MAKE) -C $@ CC=${CC} ARCH=${ARCH} CFLAGS="${CFLAGS}" LDFLAGS="${LDFLAGS}"

libsric:
	$(MAKE) -C $@ CC=${CC} ARCH=${ARCH} CFLAGS="${CFLAGS} -I`pwd`" LDFLAGS="${LDFLAGS}"

depend: *.c
	rm -f depend
	for file in $^; do \
		${CC} ${CFLAGS} -MM $$file -o - >> $@ ; \
	done ;

.PHONY: clean ${SUBDIRS}

clean:
	-rm -f motor depend *.o
	for d in ${SUBDIRS} ; do\
		${MAKE} -C $$d clean ; \
	done ;

