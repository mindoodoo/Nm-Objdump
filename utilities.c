/*
** EPITECH PROJECT, 2022
** utilities.c
** File description:
** .
*/

#include <stdio.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

void print_error(char *msg)
{
    dprintf(2, "%s", msg);
}

int skip_section(Elf64_Shdr section_header, char *name)
{
    if (section_header.sh_type == SHT_NOBITS || section_header.sh_flags == 0)
        return 1;
    if (!strcmp(name, ".shstrtab") || !strcmp(name, ".symtab") ||
    !strcmp(name, ".strtab"))
        return 1;
    return 0;
}

void *read_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    struct stat sb;
    void *start;

    if (fd < 0)
        return NULL;
    fstat(fd, &sb);
    start = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    return start;
}

int check_is_dir(char *filename)
{
    int fd = open(filename, O_RDONLY);
    struct stat sb;

    if (fd) {
        fstat(fd, &sb);
        if (S_ISDIR(sb.st_mode))
            return 1;
    }
    close(fd);
    return 0;
}

char *remove_undesired(char const *input)
{
    char *str = strdup(input);

    for (int j = 0; str[j]; j++)
        if (str[j] == '_' || str[j] == '.' || str[j] == '@') {
            strcpy(&str[j], &str[j + 1]);
            j--;
        }
    return str;
}
