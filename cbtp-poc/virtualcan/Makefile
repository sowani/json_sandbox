ifeq ($(DEBUG), 1)
  DFLAGS = -g -O0
else
  DFLAGS = -O3
endif

INCPATH = -I.

%.o: %.c
	gcc $(DFLAGS) -c -fPIC $(INCPATH) $< -o $@

all: libvcan

libvcan: vcan.o vcan.h
	ar rcs $@.a vcan.o

demo:
	cd example; make -f Makefile

install: libvcan
	mv *.a lib
	cp *.h lib

clean:
	\rm -rf *.o

cleaner:
	\rm -rf *.o lib*.a lib/*
	cd example; make clean
