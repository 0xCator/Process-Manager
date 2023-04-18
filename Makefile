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
	sudo cp ./files/SysMonitor.7 /usr/share/man/man7
	sudo mandb

$(BINARY) $(TEST): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.cr
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES) $(TEST)

uninstall:
	sudo rm -f /bin/SysMonitor  
	sudo rm -f /usr/share/man/man7/SysMonitor.7 
