PROG =
LIBRARY = libast-api.so 
LDFLAGS =
CFLAGS = -Wall -fPIC  -g
LIBOBJS = src/astman/astman.o src/astman/action.o src/sip/sipconf.o src/astapi.o src/commands/action.o src/commands/event.o src/astcore.o
INCLUDE = -I./src/inc -Iinc
LIB = 	



CC = gcc $(CFLAGS) -O0 $(INCLUDE)
LD = gcc $(LDFLAGS) $(LIB)
STRIP = strip


all: $(LIBRARY)

doc:
	@echo "Generating document with Doxygen..."
	@doxygen doxygen.cfg


$(LIBRARY): $(LIBOBJS)

libast-api.so: $(LIBOBJS)
	@echo [Creating $@ LIB]
	@$(LD) $(LIBOBJS) -shared -o $@
	@cp $@ $@.unstripped
	@$(STRIP) $@

libast-api.a: $(LIBOBJS)
	@echo [Creating $@ LIB]
	@$(AR) crv $@ 

%.o: %.c
	@echo [compiling $@]
	@$(CC) $(CFLAGS) -c $(CFLAGS) -o $@ $<


clean:
	@echo [Remove OBJ file]
	@rm -f $(LIBOBJS)
	@echo [Remove generated LIBs]
	@rm -f $(LIBRARY)
