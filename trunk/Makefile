PROG =
LIBRARY.SO = libast-api/libast-api.so
LDFLAGS =
CFLAGS = -Wall -fPIC  -g
LIBOBJS = src/astman/astman.o \
	  src/commands/action.o \
	  src/commands/connection.o \
	  src/commands/event.o \
	  src/sip/peer.o \
	  src/sip/sipconf.o \
	  src/sip/registry.o

INCLUDE = -Isrc/inc -Ilibast-api
LIB = 	


ifndef MAKEHOST
CC = mips-linux-uclibc-gcc -Wall -O0 $(INCLUDE)
LD = mips-linux-uclibc-gcc $(LIB)
STRIP = mips-linux-uclibc-strip
else
CC = gcc $(CFLAGS) -O0 $(INCLUDE)
LD = gcc $(LDFLAGS) $(LIB)
STRIP = strip
endif



all: $(LIBRARY.SO)

test:
	$(MAKE) -C test

doc:
	@echo "Generating document with Doxygen..."
	@doxygen doxygen.cfg


$(LIBRARY.SO): $(LIBOBJS)
	@echo [Creating $@ LIB]
	@$(LD) $(LIBOBJS) -shared -o $@
	@cp $@ $@.unstripped
	@$(STRIP) $@

$(LIBRARY.A): $(LIBOBJS)
	@echo [Creating $@ LIB]
	@$(AR) crv $@ 

%.o: %.c
	@echo [compiling $@]
	@$(CC) $(CFLAGS) -c $(CFLAGS) -o $@ $<


clean:
	@echo [Remove OBJ file]
	@rm -f $(LIBOBJS)
	@echo [Remove generated LIBs]
	@rm -f $(LIBRARY.SO)
	@rm -f $(LIBRARY.SO).unstripped
