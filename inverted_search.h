
#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 27
#define WORD_SIZE 50
#define FILE_SIZE 100

typedef struct sub_node
{
    char file_name[FILE_SIZE];
    int word_count;
    struct sub_node *link;
} sub_node;

typedef struct main_node
{
    char word[WORD_SIZE];
    int file_count;
    sub_node *sub_link;
    struct main_node *link;
} main_node;

typedef struct
{
    char file_name[FILE_SIZE];
    int count;
} file_entry;

int hash_function(char word[]);

int create_database(main_node *head[], char *file_names[], int file_count);

int insert_word(main_node *head[], char word[], char file_name[]);

int search_database(main_node *head[], char word[]);

void display_database(main_node *head[]);

int save_database(main_node *head[], char file_name[]);

int load_database(main_node *head[], char file_name[]);

int is_file_present(char *file_name, char *file_names[], int count);

void free_database(main_node *head[]);

#endif