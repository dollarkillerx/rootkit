all: scp.so

scp.so: scp.c
	gcc -Wall -fPIC -shared -o scp.so scp.c -ldl

.PHONY clean:
	rm -f scp.so
