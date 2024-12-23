NAME=libvec3.a

CC=clang
CFLAGS=-Wall -Werror -Wextra -std=c89
SRC=vec3_ip_mult.c \
	vec3_add.c \
	vec3_copy.c \
	vec3_cross.c \
	vec3_div_scalar.c \
	vec3_dot.c \
	vec3_ip_add.c \
	vec3_ip_div.c \
	vec3_ip_mult_scalar.c \
	vec3_ip_sub.c \
	vec3_len.c \
	vec3_mult.c \
	vec3_mult_scalar.c \
	vec3_new.c \
	vec3_print.c \
	vec3_sqrd_len.c \
	vec3_sub.c \
	vec3_unit.c

OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ)
	ar rcs $@ $^

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re