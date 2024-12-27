NAME=libft.a
SRCS=ft_strtohl.c \
	va_list_parser.c \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_char_in_s.c \
	ft_count_flags.c \
	ft_display_formatted.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c \
	ft_ltoh.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_parse_flags.c \
	ft_printf.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strrev.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_min.c \
	ft_max.c

OBJS=$(SRCS:.c=.o)
BOBJS=$(BSRCS:.c=.o)
CC=cc
CFLAGS=-Wall -Werror -Wextra
AR=ar rc
NAME_BONUS=.bonus
LIB=ranlib

$(NAME) : $(OBJS)
	$(AR) $@ $^

all : $(NAME)

$(NAME_BONUS):	$(OBJS) $(BOBJS)
	$(AR) $(NAME) $(OBJS) $(BOBJS)
	$(LIB) $(NAME)
	touch $(NAME_BONUS)

bonus : $(NAME_BONUS)

clean : 
	rm -f $(OBJS) $(BOBJS) $(NAME_BONUS)

fclean : clean
	rm -f $(NAME)

re : fclean all

default : all

.PHONY : default all re fclean clean
