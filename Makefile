CC=cc
CFLAGS=-O2 -I../.. -shared -fPIC

MINIZIP_OBJS = ioapi.o mztools.o unzip.o zip.o ../../libz.so

.c.o:
	$(CC) -c $(CFLAGS) $*.c

all: libminizip.so

libminizip.so: $(MINIZIP_OBJS)
	$(CC) $(SHARE) $(CFLAGS) -o $@ $(MINIZIP_OBJS)

test: test.o
	$(CC) $^ -o $@ -lminizip -L.

clean:
	/bin/rm -f *.o *~ libminizip.so test

