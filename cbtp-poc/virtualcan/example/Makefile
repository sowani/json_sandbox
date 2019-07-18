ifeq ($(DEBUG), 1)
  DFLAGS = -g -O0
else
  DFLAGS = -O3
endif

INCPATH = -I..
LIBPATH = -L..

%.o: %.c
	gcc $(DFLAGS) $(INCPATH) -c -fPIC $< -o $@

all: demo

demo: server client

server: server.c
	gcc $(DFLAGS) $(INCPATH) $< -o $@ $(LIBPATH) -lvcan

client: client.c
	gcc $(DFLAGS) $(INCPATH) $< -o $@ $(LIBPATH) -lvcan

clean:
	\rm -rf *.o server client
