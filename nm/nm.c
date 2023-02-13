/*
** EPITECH PROJECT, 2022
** nm.c
** File description:
** .
*/

#include "nm.h"

void display_entries(sym_t *head, unsigned char *str_table,
Elf64_Shdr *headers)
{

    while (head) {
        if (head->sym->st_value)
            printf("%016x ", head->sym->st_value);
        else
            printf("                 ");
        printf("%c ", get_type(head->sym, headers));
        printf("%s\n", str_table + head->sym->st_name);
        head = head->next;
    }
}

sym_t *parse_symbols(Elf64_Sym *sym_table, void *end_ptr,
unsigned char *str_table)
{
    sym_t *head = NULL;

    for (long unsigned int i = 1; (void *)&sym_table[i] < end_ptr; i++)
        if (sym_table[i].st_name && sym_table[i].st_shndx != SHN_ABS)
            head = push(head, &sym_table[i], str_table);
    return head;
}

void *check_args(char *filename)
{
    void *start = NULL;

    if (!(start = read_file(filename))) {
        dprintf(2, "nm: '%s': No such file\n", filename);
        return NULL;
    }
    if (check_is_dir(filename)) {
        dprintf(2, "nm: Warning: '%s' is a directory\n", filename);
        return NULL;
    }
    if (strncmp((void*)start, ELFMAG, 4)) {
        dprintf(2, "nm: %s: file format not recognized\n", filename);
        return NULL;
    }
    return start;
}

int my_nm(char *filename)
{
    Elf64_Ehdr *start;
    Elf64_Sym *sym_table;
    size_t sym_table_size;
    unsigned char *str_table;
    Elf64_Sym **sym_array;
    sym_t *list = NULL;

    start = check_args(filename);
    sym_table = get_sym_table(start); // Not the issue
    str_table = get_name_table(start); // Not an issue
    sym_table_size = get_sym_table_size(start);
    list = parse_symbols(sym_table, (void *)sym_table + sym_table_size, str_table);
    display_entries(list, str_table, (void *)start + start->e_shoff);
}

int main(int ac, char **av)
{
    int exit_code = 0;

    if (ac > 2)
        for (int i = 1; av[i]; i++) {
            if (!check_args(av[i])) {
                exit_code = 1;
                continue;
            } else {
                printf("\n%s\n", av[i]);
                my_nm(av[i]);
            }
        }
    else {
        if (check_args(av[1]))
            my_nm(av[1]);
        else
            exit_code = 1;
    }
    return (exit_code ? 84 : 0);
}
