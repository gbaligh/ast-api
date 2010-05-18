CC=gcc
CFLAGS=-c -Wall
LDFLAGS= -L../libast-api -last-api
SOURCES=sampleAction.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=action
INCLUDE=-I../src/inc -I../libast-api

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(INCLUDE) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(INCLUDE) $(LDFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
