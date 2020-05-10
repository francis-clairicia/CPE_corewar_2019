##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

SRC_NO_TEST			=	src/main.c

SRC_TEST			=	src/help/help.c						\
						src/parsing/parser.c				\
						src/parsing/args.c					\
						src/init/init.c						\
						src/champion/add_champion.c			\
						src/champion/check_champion.c		\
						src/champion/sort_champion.c		\
						src/memory/handle_mem.c				\
						src/memory/print_dump.c				\
						src/game/game_loop.c				\
						src/game/check_end.c				\
						src/mnemonic/mne_add.c				\
						src/mnemonic/mne_aff.c				\
						src/mnemonic/mne_and.c				\
						src/mnemonic/mne_fork.c				\
						src/mnemonic/mne_ld.c				\
						src/mnemonic/mne_ldi.c				\
						src/mnemonic/mne_lfork.c			\
						src/mnemonic/mne_live.c				\
						src/mnemonic/mne_lld.c				\
						src/mnemonic/mne_lldi.c				\
						src/mnemonic/mne_or.c				\
						src/mnemonic/mne_st.c				\
						src/mnemonic/mne_sti.c				\
						src/mnemonic/mne_sub.c				\
						src/mnemonic/mne_xor.c				\
						src/mnemonic/mne_zjmp.c				\
						src/mnemonic/utils_mnemonic.c		\
						src/mnemonic/utils_mnemonic_two.c	\
						src/free/free.c						\
						src/free/free_battle.c				\
						src/free/free_champ.c				\
						src/utils/rev_nb.c					\
						src/utils/ret_putstr_fd.c			\
						src/corewar.c						\
						src/op.c

SRC					=	$(SRC_NO_TEST) $(SRC_TEST)

CFLAGS				=	-Wall -Wextra

CPPFLAGS			=	-I./include/

override LDFLAGS	+=	-L../lib

override LDLIBS		+=	-lmy

OBJ					=	$(SRC:.c=.o)

NAME				=	corewar

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
	rm -f $(NAME)

re:	fclean all

.PHONY:	all -lmy tests_run debug clean fclean re