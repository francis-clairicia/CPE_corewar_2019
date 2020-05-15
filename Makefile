##
## EPITECH PROJECT, 2019
## CPE_corewar_2019
## File description:
## Makefile
##

ASM		=	asm

COREWAR	=	corewar

all:
	$(MAKE) -C $(ASM)
	$(MAKE) -C $(COREWAR)

lib:
	$(MAKE) -C lib/my
	cp include/*.h $(ASM)/include/
	cp include/*.h $(COREWAR)/include/

clean:
	$(MAKE) clean -C lib/my
	$(MAKE) clean -C $(ASM)
	$(MAKE) clean -C $(COREWAR)

fclean:
	$(MAKE) fclean -C lib/my
	$(MAKE) fclean -C $(ASM)
	$(MAKE) fclean -C $(COREWAR)

tests_run:
	$(MAKE) tests_run -C $(ASM)
	$(MAKE) tests_run -C $(COREWAR)

bonus:	all
	cp $(ASM)/$(ASM) bonus/python/$(ASM)/asm_compiler
	cp $(COREWAR)/$(COREWAR) bonus/ncurses/
	cp $(COREWAR)/$(COREWAR) bonus/python/

re:	fclean all

.PHONY: all lib clean fclean tests_run bonus re