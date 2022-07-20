cc=gcc
cflags=-fPIC -O3 -Wall -Wextra -Werror=format-security

main:
	$(cc) -o mc-loadshader loadshader.c $(cflags) 
