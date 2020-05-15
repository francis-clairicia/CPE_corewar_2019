##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

SRC					=	src/main.c					\
						src/check_env.c				\
						src/bonus_vm.c				\
						src/game/init_game.c		\
						src/game/game_loop.c

CFLAGS				=	-Wall -Wextra

CPPFLAGS			=	-I./include/

override LDFLAGS	+=	-L../../lib

override LDLIBS		+=	-lmy

OBJ					=	$(SRC:.c=.o)

NAME				=	ncurses_bonus

all:	$(NAME)

$(NAME):	CFLAGS += -O2
$(NAME):	$(LDLIBS) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS) -lncurses

-lmy:
	$(MAKE) lib -C ../..

debug:	CFLAGS += -g
debug:	$(LDLIBS)
	$(CC) -o $(NAME) $(SRC) $(LDFLAGS) $(LDLIBS) $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	make fclean -C ../../lib/my
	rm -f $(NAME)

re:	fclean all

.PHONY:	all -lmy debug clean fclean re