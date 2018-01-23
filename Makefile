SRC :=  external
BIN :=  bin

objects = ls mkdir date rm cat

all: $(objects) ki11

$(shell mkdir -p bin)

$(objects): %: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $(BIN)/$@ $<

ki11: main.c
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm -rf $(BIN) ki11
