/*
** EPITECH PROJECT, 2022
** flags.c
** File description:
** .
*/

#include "objdump.h"

void print_correct_flag(Elf64_Ehdr *header)
{
    int flg = 0;

    if (header->e_type == ET_REL) {
        flg += HAS_SYMS + HAS_RELOC;
        printf("0x%08x:\nHAS_RELOC, HAS_SYMS\n", flg);
    }
    if (header->e_type == ET_DYN) {
        flg += D_PAGED + DYNAMIC + HAS_SYMS;
        printf("0x%08x:\nHAS_SYMS, DYNAMIC, D_PAGED\n", flg);
    }
    if (header->e_type == ET_EXEC) {
        flg += EXEC_P + HAS_SYMS + D_PAGED;
        printf("0x%08x:\nEXEC_P, HAS_SYMS, D_PAGED\n", flg);
    }
}
