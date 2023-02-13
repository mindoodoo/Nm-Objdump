/*
** EPITECH PROJECT, 2022
** nm.h
** File description:
** .
*/

#pragma once

#include <stdio.h>
#include <elf.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

typedef struct sym_s {
    struct sym_s *next;
    struct sym_s *previous;
    Elf64_Sym *sym;
} sym_t;

void print_error(char *msg);
void *read_file(const char *filename);
void *get_name_table(Elf64_Ehdr *start);
void *get_sym_table(Elf64_Ehdr *start);
Elf64_Xword get_sym_table_size(Elf64_Ehdr *start);
sym_t *push(sym_t *head, Elf64_Sym *sym, char *str_table);
char get_type(Elf64_Sym *sym, Elf64_Shdr *headers);
int check_is_dir(char *filename);
char *remove_undesired(char const *input);
