BINARY=SysMonitor
TEST=./src/out.test
CODEDRIVE=./src
HEADERS=./headers/


CC=gcc

DEPFLAGS=-MP -MD

CFLAGS=-g $(foreach I,$(HEADERS),-I$(I)) $(DEPFLAGS)
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

CFILES=$(foreach I,$(CODEDRIVE),$(wildcard $(I)/*.c))

OBJECTS=$(patsubst %.c,%.o,$(CFILES))

test:$(TEST)

install: $(BINARY)
	sudo mv $(BINARY) /bin/$(BINARY)

$(BINARY) $(TEST): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES) $(TEST)
