objects = ls mkdir date rm cat
all: $(objects)

$(objects): %: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(objects) 
