##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SRC			=	my_put_nbr.c				\
				my_strcpy.c					\
				my_putchar.c				\
				my_showstr.c				\
				my_sort_int_array.c			\
				my_str_isupper.c			\
				my_strcmp.c					\
				my_showmem.c				\
				my_strstr.c					\
				my_revstr.c					\
				my_find_prime_sup.c			\
				my_strcapitalize.c			\
				my_strncpy.c				\
				my_str_isalpha.c			\
				my_str_isalphanum.c			\
				my_strcat.c					\
				my_compute_square_root.c	\
				my_is_prime.c				\
				my_str_isnum.c				\
				my_getnbr.c					\
				my_strupcase.c				\
				my_str_islower.c			\
				my_strlen.c					\
				my_putstr.c					\
				my_strncmp.c				\
				my_str_isprintable.c		\
				my_strncat.c				\
				my_compute_power_rec.c		\
				my_strlowcase.c				\
				my_str_to_word_array.c		\
				my_show_word_array.c		\
				my_array_len.c				\
				my_array_dup.c				\
				my_strdup.c					\
				my_strndup.c				\
				my_swap.c					\
				my_strchr.c					\
				convert_base.c				\
				my_putnbr_base.c			\
				my_getnbr_base.c			\
				my_nbr_to_str.c				\
				my_nbr_len.c				\
				get_next_line.c				\
				join_path.c					\
				my_str_contains_only.c		\
				my_memset.c					\
				my_malloc_array.c			\
				my_array_contains.c

LINKED_LIST	=	list/my_list.c				\
				list/my_create_node.c		\
				list/my_insert_in_list.c	\
				list/my_list_to_str.c		\
				list/my_list_to_2d_array.c	\
				list/my_concat_str_list.c	\
				list/my_free_list.c			\
				list/my_concat_list.c		\
				list/my_rev_list.c			\
				list/my_node.c				\
				list/my_node_from.c			\
				list/my_find_node.c			\
				list/my_delete_node.c		\
				list/my_delete_node_from.c

PRINTF		=	printf/my_printf.c					\
				printf/my_dprintf.c					\
				printf/my_printf_number.c			\
				printf/my_printf_str.c				\
				printf/my_printf_pointer.c			\
				printf/my_printf_binary.c			\
				printf/my_printf_octal.c			\
				printf/my_printf_decimal.c			\
				printf/my_printf_hexa_lower.c		\
				printf/my_printf_hexa_upper.c		\
				printf/my_printf_get_infos.c		\
				printf/my_printf_get_modifiers.c	\
				printf/my_printf_flag_errors.c		\
				printf/my_printf_modifier.c			\
				printf/my_putnbr_for_printf.c		\
				printf/my_nbr_len_u.c				\
				printf/convert_base_for_printf.c

CFLAGS		=	-Wall -Wextra

override CPPFLAGS	+=	-I./ -I./printf -I./list

OBJ	=	$(SRC:.c=.o) $(LINKED_LIST:.c=.o) $(PRINTF:.c=.o)

NAME	=	libmy.a

all:	$(NAME)

$(NAME):	$(OBJ)
	$(AR) rc $(NAME) $(OBJ)
	cp -u $(NAME) ../
	mkdir -p ../../include
	cp ./my.h ./list/mylist.h ../../include

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) ../$(NAME)

re:	fclean all

.PHONY: all clean fclean re