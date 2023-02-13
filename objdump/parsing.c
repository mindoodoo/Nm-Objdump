/*
** EPITECH PROJECT, 2022
** parsing.c
** File description:
** .
*/

#include "objdump.h"

void print_header(void *start, char *filename)
{
    Elf64_Ehdr *header = start;

    printf("\n");
    printf("%s:     file format elf64-x86-64\n", filename);
    printf("architecture: i386:x86-64, flags ");
    print_correct_flag(header);
    printf("start address %018p\n\n", header->e_entry);
}

void print_hexa(char *ptr, void *end_ptr)
{
    for (int i = 0; i < 16; i++) {
        if (i % 4 == 0)
            printf(" ");
        if (((void *)ptr + i) >= end_ptr) {
            printf("  ");
            continue;
        }
        printf("%02x", *((unsigned char *)(ptr) + i));
    }
    printf("  ");
    for (int i = 0; i < 16; i++) {
        if (((void *)ptr + i) >= end_ptr) {
            printf(" ");
            continue;
        }
        if (*((unsigned char *)(ptr) + i) < 32 ||
        *((unsigned char *)(ptr) + i) > 126)
            printf(".");
        else
            printf("%c", *((unsigned char *)(ptr) + i));
    }
}

// printf("DATA1 : %x   DATA2: %x\n",
// section[i].sh_addr, *((char *)(start + section[i].sh_offset) + 1))

int get_offset_width(size_t size, size_t start_offset)
{
    size_t max_offset = start_offset + size;
    char *str = malloc(sizeof(char) * 1000);
    int width = 4;

    sprintf(str, "%x", max_offset);
    width = strlen(str);
    free(str);
    if (width < 4)
        return 4;
    else
        return width;
}

// Is that last argument really needed ?
void print_content(void *sec_start, size_t size, size_t start_offset)
{
    for (size_t offset = 0; offset < size; offset += 16) {
        printf(" %0*x", get_offset_width(size, start_offset),
        offset + start_offset);
        print_hexa(sec_start + offset, (sec_start + size));
        printf("\n");
    }
}

void print_sections(Elf64_Ehdr *start)
{
    Elf64_Shdr *section_headers = (void *)start + start->e_shoff;
    unsigned int section_count = start->e_shnum;
    char *name_table = (void *)start +
    section_headers[start->e_shstrndx].sh_offset;
    char *name = NULL;
    void *data_start = NULL;

    for (int i = 0; i < section_count; i++) {
        name = name_table + section_headers[i].sh_name;
        if (skip_section(section_headers[i], name))
            continue;
        printf("Contents of section %s:\n", name);
        data_start = (void *)start + section_headers[i].sh_offset;
        print_content(data_start, section_headers[i].sh_size,
        section_headers[i].sh_addr);
    }
}
