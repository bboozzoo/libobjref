CFLAGS += -ggdb -I.
LDFLAGS += -L.
LIBOBJREF_SRC = objref.c
TEST_OBJREF_SRC = test.c

all: libobjref.so test-objref

libobjref.so: $(LIBOBJREF_SRC:.c=.o)
	$(CC) -shared -o $@ $^ 

test-objref: $(TEST_OBJREF_SRC:.c=.o)
	$(CC) -o $@ $^ $(LDFLAGS) -lobjref

%.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS)
clean:
	rm -f *.o *.so