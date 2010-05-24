##----------------------------------------------------------------------------
# Created with genmake.pl v1.1 on Mon May 24 02:18:12 2010
# genmake.pl home: http://muquit.com/muquit/software/
# Copryright: GNU GPL (http://www.gnu.org/copyleft/gpl.html)
##----------------------------------------------------------------------------
rm=/bin/rm -f
CC= gcc -fPIC
LINK= gcc -shared
DEFS=  
AR= ar cq
RANLIB= /usr/bin/ranlib
LIBNAME= astapi/libastapi.so

INCLUDES=  -I. -I./include -I./astapi

DEFINES= $(INCLUDES) $(DEFS) -DSYS_UNIX=1 -DAST_API_DEBUG=1
CFLAGS= -g $(DEFINES)

SRCS = object/category.c object/config.c object/connection.c object/general.c object/peer.c object/registry.c object/trunk.c object/user.c astman/action.c astman/astevent.c astman/astman.c astman/update.c 

OBJS = object/category.o object/config.o object/connection.o object/general.o object/peer.o object/registry.o object/trunk.o object/user.o astman/action.o astman/astevent.o astman/astman.o astman/update.o 

.c.o:
	$(rm) -f $@
	$(CC) $(CFLAGS) -c $*.c -o $@

all: $(LIBNAME)

$(LIBNAME) : $(OBJS)
	$(rm) $@
	$(LINK) -o $(LIBNAME) $(OBJS)


clean:
	$(rm) $(OBJS) $(LIBNAME) core *~
