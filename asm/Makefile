##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

SRC_NO_TEST			=	src/main.c

SRC_TEST			=	src/asm.c									\
						src/op.c									\
						src/print_error.c							\
						src/parsing/read_file.c						\
						src/parsing/create_lines.c					\
						src/parsing/header.c						\
						src/parsing/parse_line.c					\
						src/parsing/valid_instruction.c				\
						src/parsing/valid_parameters.c				\
						src/parsing/valid_label.c					\
						src/parsing/my_strip_str.c					\
						src/instructions/instructions.c				\
						src/instructions/init_instruction.c			\
						src/instructions/add_new_instruction.c		\
						src/instructions/get_parameters.c			\
						src/instructions/add_parameters.c

SRC					=	$(SRC_NO_TEST) $(SRC_TEST)

CFLAGS				=	-Wall -Wextra

CPPFLAGS			=	-I./include/

override LDFLAGS	+=	-L../lib

override LDLIBS		+=	-lmy

OBJ					=	$(SRC:.c=.o)

NAME				=	asm

all:	$(NAME)

$(NAME):	CFLAGS += -O2
$(NAME):	$(LDLIBS) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

-lmy:
	$(MAKE) lib -C ..

tests_run:	CFLAGS += --coverage
tests_run:	LDLIBS += -lcriterion
tests_run:	$(LDLIBS)
	@find -name "*.gc*" -delete
	$(CC) -o unit_tests $(SRC_TEST) tests/*.c $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)
	-./unit_tests
	$(RM) unit_tests test*.gc*
	mkdir -p coverage
	mv *.gc* coverage/

debug:	CFLAGS += -g
debug:	$(LDLIBS)
	$(CC) -o $(NAME) $(SRC) $(LDFLAGS) $(LDLIBS) $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) unit_tests *.gc*

fclean:	clean
	make fclean -s -C ../lib/my
	rm -f $(NAME)

re:	fclean all

.PHONY:	all -lmy tests_run debug clean fclean re
