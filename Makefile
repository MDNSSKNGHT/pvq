CC		= cc
CFLAGS	= -Wall -Wextra -lm
OBJ		= main.o

pvq: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: pvq
	./pvq

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f pvq *.o
