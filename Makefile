ifeq ($(DEBUG), 1)
  DFLAGS = -g -O0
else
  DFLAGS = -O3
endif

%.o: %.c
	gcc -g -c -fPIC $(INCPATH) $< -o $@

all: libvcan demo

libvcan: vcan.o vcan.h
	ar rcs $@.a vcan.o

demo:
	cd example; make -f Makefile

clean:
	\rm -rf *.o

cleaner:
	\rm -rf *.o lib*.a
	cd example; make clean
