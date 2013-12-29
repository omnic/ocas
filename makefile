CC = clang
CFLAGS = -O2 -march=native -mtune=native

all:	build/ocas

clean:	build
	rm -rvf build

build:
	mkdir -pv build

build/ocas:	build/ocas.o build/as.o
	$(CC) build/ocas.o build/as.o -o build/ocas

build/ocas.o:	build ocas.c ocas.h
	$(CC) ocas.c -c -o build/ocas.o $(CFLAGS)

build/as.o:	build as.c as.h ocas.h
	$(CC) as.c -c -o build/as.o $(CFLAGS)
