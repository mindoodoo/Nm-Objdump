/*
** EPITECH PROJECT, 2022
** symbol_type.c
** File description:
** .
*/

#include "nm.h"

char type_char_one(Elf64_Sym *sym)
{
    switch (ELF64_ST_BIND(sym->st_info)) {
        case STB_GNU_UNIQUE:
            return 'u';
            break;
        case STB_WEAK:
            if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT) {
                if (sym->st_shndx == SHN_UNDEF)
                    return 'v';
                else
                    return 'V';
            }
            if (sym->st_shndx == SHN_UNDEF)
                return 'w';
            else
                return 'W';
            break;
    }
    return 0;
}

char type_char_two(Elf64_Sym *sym)
{
    switch (sym->st_shndx) {
        case SHN_UNDEF:
            return 'U';
            break;
        case SHN_ABS:
            return 'A';
            break;
        case SHN_COMMON:
            return 'C';
            break;
    }
    return 0;
}

char type_char_three(Elf64_Sym *sym, Elf64_Shdr *headers)
{
    switch (headers[sym->st_shndx].sh_type) {
        case SHT_NOBITS:
            if (headers[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
                return 'B';
            break;
        case SHT_PROGBITS:
            if (headers[sym->st_shndx].sh_flags == SHF_ALLOC)
                return 'R';
            if (headers[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
                return 'D';
            if (headers[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
                return 'T';
            break;
        case SHT_DYNAMIC:
            return 'D';
            break;
    }
    return 0;
}

char get_type(Elf64_Sym *sym, Elf64_Shdr *headers)
{
    if (type_char_one(sym))
        return type_char_one(sym);
    if (type_char_two(sym))
        return type_char_two(sym);
    if (type_char_three(sym, headers))
        return type_char_three(sym, headers);
    return '?';
}
