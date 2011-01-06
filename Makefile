CFLAGS += -I.
LDFLAGS += -L.
LIBOBJREF_SRC = objref.c

all: libobjref.so test-objref

libobjref.so: $(LIBOBJREF_SRC:.c=.o)
	$(CC) -shared -o $@ $^ 

test-objref:
	$(CC) -o $@ $^ -lobjref