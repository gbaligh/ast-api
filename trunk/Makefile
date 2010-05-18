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


CC = gcc $(CFLAGS) -O0 $(INCLUDE)
LD = gcc $(LDFLAGS) $(LIB)
STRIP = strip



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

install:
	@echo [installing LIB to the system]
