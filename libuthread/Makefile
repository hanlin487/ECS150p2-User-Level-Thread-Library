# Target library
lib := libuthread.a
FLAGS := -Wall -Wextra -Werror -g
SRCFILES := queue.c uthread.c context.c sem.c preempt.c

all: $(lib)

<<<<<<< HEAD
$(lib): queue.o uthread.o context.o sem.o 
=======
## TODO: Phase 1
$(lib): queue.o uthread.o context.o sem.o preempt.o
>>>>>>> 58a27be20e34297f1f577cc9207c9bad99bab46b
	ar rcs $(lib) $^

%.o : %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	rm -f $(lib) queue.o uthread.o context.o sem.o preempt.o
