all: 1.5-compress

1.5-compress: 1.5-compress.c
	gcc -o $@ $@.c

%: %.c
	gcc %.c -o %

clean:
	rm %	
