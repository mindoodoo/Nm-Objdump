/*
** EPITECH PROJECT, 2022
** sym_array.c
** File description:
** .
*/

#include "nm.h"

int my_strcmp(char const *s1, char const *s2)
{
    char *copy1 = remove_undesired(s1);
    char *copy2 = remove_undesired(s2);
    int output = strcasecmp(copy1, copy2);

    free(copy1);
    free(copy2);
    return output;
}

void insert(sym_t *next, sym_t *new_node)
{
    new_node->next = next;
    new_node->previous = next->previous;
    if (new_node->previous)
        new_node->previous->next = new_node;
    next->previous = new_node;
}

void insert_at_end(sym_t *last, sym_t *new_node)
{
    last->next = new_node;
    new_node->previous = last;
}

void push_loop(sym_t *head, char *str_table, sym_t *new_node, Elf64_Sym *sym)
{
    sym_t *temp_head = head;

    while (temp_head) {
        if (my_strcmp(str_table + sym->st_name,
        str_table + temp_head->sym->st_name) <= 0) {
            insert(temp_head, new_node);
            break;
        }
        if (!temp_head->next) {
            insert_at_end(temp_head, new_node);
            break;
        }
        temp_head = temp_head->next;
    }
}

sym_t *push(sym_t *head, Elf64_Sym *sym, char *str_table)
{
    sym_t *new_node = malloc(sizeof(sym_t));

    new_node->sym = sym;
    new_node->previous = NULL;
    new_node->next = NULL;
    if (!head)
        return new_node;
    else {
        push_loop(head, str_table, new_node, sym);
    }
    if (!new_node->previous)
        return new_node;
    return head;
}
