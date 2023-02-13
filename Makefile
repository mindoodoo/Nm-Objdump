##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## .
##

CFLAGS = -I./include

NMSRC = nm/nm_utilities.c \
	nm/nm.c \
	nm/sym_list.c \
	nm/symbol_type.c \
	utilities.c

NMOBJ = $(NMSRC:.c=.o)

OBJSRC	= objdump/flags.c \
	objdump/objdump.c \
	objdump/parsing.c \
	utilities.c

OBJOBJ = $(OBJSRC:.c=.o)

all: objdump nm

nm: $(NMOBJ)
	gcc	-o my_nm $(NMOBJ) $(CFLAGS)

objdump: $(OBJOBJ)
	gcc	-o my_objdump $(OBJOBJ) $(CFLAGS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf my_nm my_objdump

re: fclean all

.PHONY: re fclean clean