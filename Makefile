CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
LDLIBS = -lm

.PHONY: clean all run zip

all: primes primes-i steg-decode

#primes
primes: primes.o eratosthenes.o	error.o bitset.o
	gcc primes.o eratosthenes.o error.o bitset.o -o primes $(LDLIBS)

primes.o: primes.c bitset.h
	gcc $(CFLAGS) -c primes.c -o primes.o

eratosthenes.o: eratosthenes.c bitset.h
	gcc $(CFLAGS) -c eratosthenes.c -o eratosthenes.o

error.o: error.c error.h
	gcc $(CFLAGS) -c error.c -o error.o

bitset.o: bitset.c bitset.h
	gcc $(CFLAGS) -c bitset.c -o bitset.o

#primes-i
primes-i: primes-i.o eratosthenes-i.o error.o bitset-i.o
	gcc primes-i.o eratosthenes-i.o error.o bitset-i.o -o primes-i $(LDLIBS)

primes-i.o: primes.c bitset.h
	gcc $(CFLAGS) -DUSE_INLINE -c primes.c -o primes-i.o

bitset-i.o: bitset.c bitset.h
	gcc $(CFLAGS) -DUSE_INLINE -c bitset.c -o bitset-i.o

eratosthenes-i.o: eratosthenes.c bitset.h
	gcc $(CFLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-i.o

#steg-decode:
steg-decode: steg-decode.o ppm.o error.o bitset.o eratosthenes.o
	gcc steg-decode.o ppm.o error.o bitset.o eratosthenes.o -o steg-decode $(LDLIBS)

steg-decode.o: steg-decode.c bitset.h ppm.h
	gcc $(CFLAGS) -c steg-decode.c -o steg-decode.o

ppm.o: ppm.c ppm.h error.h
	gcc $(CFLAGS) -c ppm.c -o ppm.o

clean:
	rm -f *.o primes primes-i steg-decode

run: primes primes-i
	./primes
	./primes-i

zip:
	zip xkocia19.zip *.c *.h Makefile
