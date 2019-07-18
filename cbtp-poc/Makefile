ifeq ($(DEBUG), 1)
  DFLAGS = -g -O0
else
  DFLAGS = -O3
endif

INCPATH = -I.
LIBPATH = -L.

CFILES = \
	cbtputil.c

HEADERS = \
	cbtp.h \
	cbtputil.h

%.o: %.c
	gcc $(DFLAGS) -c -fPIC $(INCPATH) $< -o $@

all: libcbtp

libcbtp: cbtputil.o $(HEADERS)
	ar rcs $@.a cbtputil.o

#install: libcbtp
#	mv *.a lib
#	cp *.h lib

check: check.o libcbtp
	gcc $(DFLAGS) $< -o $@ $(INCPATH) $(LIBPATH) -lcbtp

clean:
	\rm -rf *.o

cleaner:
	\rm -rf *.o lib*.a
