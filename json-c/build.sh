#!/bin/bash

#gcc example.c -I./include/json-c -L./lib -ljson-c
#gcc demo.c -I./include/json-c -L./lib -ljson-c
#gcc demo-my.c -g -I./include/json-c -L./lib -ljson-c
#gcc itr.c -I./include/json-c -L./lib -ljson-c
#gcc reader.c -I./include/json-c -L./lib -ljson-c
#gcc fwparse.c -g -I./include/json-c -L./lib -ljson-c
gcc writer.c -g -I./include/json-c -L./lib -ljson-c
