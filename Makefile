CC = g++
CFLAGS = -g -shared -fPIC
INCS = -I./ -I/usr/local/libvmime/include 
LDS = -L/usr/local/lib/ -L/usr/local/libvmime/lib/ -lvmime -liconv

AR = ar
ARFLAGS = rcv

OBJS = libmailparsedv2.a
EXAMPLE = example

#setuplibvmime:
#	cd libvmime; sh ./configure --enable-platform-posix --disable-sasl --disable-tls; make; make install; /sbin/ldconfig; cd -;

all:	$(OBJS) $(EXAMPLE);

mailparse.o:	mailparse.cpp 
	$(CC) $(CFLAGS) -c -o mailparse.o mailparse.cpp $(INCS) $(LDS)

$(OBJS):	mailparse.o
	$(AR) $(ARFLAGS) $(OBJS) mailparse.o

$(EXAMPLE): libmailparsedv2.a
	gcc -g -o $(EXAMPLE) example.c libmailparsedv2.a $(INCS) $(LDS)


clean:
	cd libvmime; make clean; cd -;
	rm -f $(OBJS)	
	rm -f $(EXAMPLE)
	rm -f *.so
	rm -f *.a
	rm -f *.o




