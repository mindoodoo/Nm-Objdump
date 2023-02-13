/*
** EPITECH PROJECT, 2022
** objdump.c
** File description:
** .
*/

#include "objdump.h"

void *check_args(char *filename)
{
    void *start = NULL;

    if (!(start = read_file(filename))) {
        dprintf(2, "objdump: '%s': No such file\n", filename);
        return NULL;
    }
    if (check_is_dir(filename)) {
        dprintf(2, "objdump: Warning: '%s' is a directory\n", filename);
        return NULL;
    }
    if (strncmp((void*)start, ELFMAG, 4)) {
        dprintf(2, "objdump: %s: file format not recognized\n", filename);
        return NULL;
    }
    return start;
}

int my_objdump(char *filename)
{
    void *start;

    if (!(start = read_file(filename))) {
        print_error("Invalid input filepath\n");
        return 84;
    }
    print_header(start, filename);
    print_sections(start);
}

int main(int ac, char **av)
{
    int exit_code = 0;

    if (ac > 2)
        for (int i = 1; av[i]; i++) {
            if (!check_args(av[i])) {
                exit_code = 1;
                continue;
            } else
                my_objdump(av[i]);
        }
    else {
        if (check_args(av[1]))
            my_objdump(av[1]);
        else
            exit_code = 1;
    }
    return (exit_code ? 84 : 0);
}
