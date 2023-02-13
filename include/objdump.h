/*
** EPITECH PROJECT, 2022
** objdump.h
** File description:
** .
*/

#pragma once

#include <stdio.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include "flags.h"

void print_error(char *msg);
int skip_section(Elf64_Shdr section_header, char *name);
void print_header(void *start, char *filename);
void print_sections(Elf64_Ehdr *start);
void *read_file(const char *filename);
char *get_machine_name(int machine_type);
void print_correct_flag(Elf64_Ehdr *header);
int check_is_dir(char *filename);
