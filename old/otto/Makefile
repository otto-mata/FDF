NAME=otto.a
SRC=list_del.c \
    list_clear.c \
    list_append.c \
    list_new.c
HEADERS=-I.
OBJS=$(patsubst %.c,%.o,$(SRC))
CC=cc
CFLAGS=-Wall -Werror -Wextra -g3

$(NAME) : $(OBJS)
	ar rc $(NAME) $^

%.o : %.c
	$(CC) -c $(HEADERS) -o $@ $^ $(CFLAGS)


all : $(NAME)

bonus : $(BOBJS) $(OBJS)
	ar rc $(NAME) $^

clean : 
	rm -f *.o

fclean : clean
	rm -f $(NAME)

re : fclean all

default : all

.PHONY : default all re fclean clean