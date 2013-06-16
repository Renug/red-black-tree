CC=g++
CFLAGS=-c -g -Wall
LINKER=g++
LFLAGS=-g -Wall
OBJECTS=run.o node.o tree.o
TARGET=red-black

$(TARGET):$(OBJECTS)
	$(LINKER) $(LFLAGS) $(OBJECTS) -o $(TARGET)

run.o:run.cpp node.h
	$(CC) $(CFLAGS) -o $@ $<

node.o:node.cpp node.h
	$(CC) $(CFLAGS) -o $@ $<

tree.o:tree.cpp tree.h node.h node.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET) $(OBJECTS)
