/*
** EPITECH PROJECT, 2022
** nm_utilities.c
** File description:
** .
*/

#include "nm.h"

void *get_name_table(Elf64_Ehdr *start)
{
    Elf64_Shdr *section_headers = (void *)start + start->e_shoff;
    Elf64_Shdr *sym_header = NULL;

    for (int i = 0; i < start->e_shnum; i++)
        if (section_headers[i].sh_type == SHT_SYMTAB) {
            sym_header = &section_headers[i];
            break;
        }
    return (void *)((void *)start +
    section_headers[sym_header->sh_link].sh_offset);
}

void *get_sym_table(Elf64_Ehdr *start)
{
    Elf64_Shdr *section_headers = (void *)start + start->e_shoff;

    for (int i = 0; i < start->e_shnum; i++)
        if (section_headers[i].sh_type == SHT_SYMTAB)
            return ((void *)start + section_headers[i].sh_offset);
    return NULL;
}

Elf64_Xword get_sym_table_size(Elf64_Ehdr *start)
{
    Elf64_Shdr *section_headers = (void *)start + start->e_shoff;

    for (int i = 0; i < start->e_shnum; i++)
        if (section_headers[i].sh_type == SHT_SYMTAB)
            return section_headers[i].sh_size;
    return 0;
}
