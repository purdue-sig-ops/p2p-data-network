files = *.c */*/*.c

all : $(files)
	cc -pthread -o chord $(files)

