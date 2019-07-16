ifeq ($(DEBUG), 1)
  DFLAGS = -g -O0
else
  DFLAGS = -O3
endif

INCPATH = -I..
LIBPATH = -L..

%.o: %.c
	gcc $(INCPATH) -g -c -fPIC $< -o $@

all: demo

demo: server client

server: server.c
	gcc $(INCPATH) -g $< -o $@ $(LIBPATH) -lvcan

client: client.c
	gcc $(INCPATH) -g $< -o $@ $(LIBPATH) -lvcan

clean:
	\rm -rf *.o server client
