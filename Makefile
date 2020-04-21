##
## EPITECH PROJECT, 2019
## CPE_corewar_2019
## File description:
## Makefile
##

ASM		=	asm

COREWAR	=	corewar

all:
	$(MAKE) -C $(ASM)_dir
	$(MAKE) -C $(COREWAR)_dir
	cp $(ASM)_dir/$(ASM) .
	cp $(COREWAR)_dir/$(COREWAR) .

lib:
	$(MAKE) -C lib/my
	cp include/*.h $(ASM)_dir/include/
	cp include/*.h $(COREWAR)_dir/include/

clean:
	$(MAKE) clean -C lib/my
	$(MAKE) clean -C $(ASM)_dir
	$(MAKE) clean -C $(COREWAR)_dir

fclean:
	$(MAKE) fclean -C lib/my
	$(MAKE) fclean -C $(ASM)_dir
	$(RM) $(ASM)
	$(MAKE) fclean -C $(COREWAR)_dir
	$(RM) $(COREWAR)

tests_run:
	$(MAKE) tests_run -C $(ASM)_dir
	$(MAKE) tests_run -C corewar

re:	fclean all

.PHONY: all lib clean fclean tests_run re