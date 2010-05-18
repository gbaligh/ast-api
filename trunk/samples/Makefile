CFLAGS = -Wall -fPIC  -g
INCLUDE = -I../inc
LIB = -L../ -last	


BIN_CONNECTION = connection
OBJ_CONNECTION = connection.o

BINS = $(BIN_CONNECTION)
OBJS = $(OBJ_CONNECTION)

SAMPLES = $(BINS)


all: $(SAMPLES)


$(BIN_CONNECTION): $(OBJ_CONNECTION)


%.o: %.c
	@echo [compiling $@]
	@$(CC) $(CFLAGS) $(LIB) $(INCLUDE) -c $(CFLAGS) -o $@ $<

