
#include "inverted_search.h"

int hash_function(char word[])
{
    char ch = tolower((unsigned char)word[0]);

    if (ch >= 'a' && ch <= 'z')
        return ch - 'a';

    return 26;
}

int insert_word(main_node *head[], char word[], char file_name[])
{
    int index = hash_function(word);

    main_node *temp = head[index];
    main_node *prev = NULL;

    while (temp != NULL)
    {
        if (strcmp(temp->word, word) == 0)
            break;

        prev = temp;
        temp = temp->link;
    }

    if (temp == NULL)
    {
        main_node *new_main = malloc(sizeof(main_node));

        if (new_main == NULL)
            return -1;

        strcpy(new_main->word, word);
        new_main->file_count = 0;
        new_main->sub_link = NULL;
        new_main->link = NULL;

        if (prev == NULL)
            head[index] = new_main;
        else
            prev->link = new_main;

        temp = new_main;
    }

    sub_node *sub = temp->sub_link;

    while (sub != NULL)
    {
        if (strcmp(sub->file_name, file_name) == 0)
        {
            sub->word_count++;
            return 0;
        }

        sub = sub->link;
    }

    sub_node *new_sub = malloc(sizeof(sub_node));

    if (new_sub == NULL)
        return -1;

    strcpy(new_sub->file_name, file_name);
    new_sub->word_count = 1;
    new_sub->link = temp->sub_link;

    temp->sub_link = new_sub;
    temp->file_count++;

    return 0;
}

int create_database(main_node *head[], char *file_names[], int file_count)
{
    FILE *fp;
    char word[WORD_SIZE];
    int i, j;

    for (i = 0; i < file_count; i++)
    {
        fp = fopen(file_names[i], "r");

        if (fp == NULL)
        {
            printf("Cannot open file: %s\n", file_names[i]);
            continue;
        }

        printf("Reading file: %s\n", file_names[i]);

        while (fscanf(fp, "%49s", word) == 1)
        {
            int len = strlen(word);
            int k = 0;

            char clean_word[WORD_SIZE];

            for (j = 0; j < len && k < WORD_SIZE - 1; j++)
            {
                if (isalnum((unsigned char)word[j]))
                {
                    clean_word[k++] =
                        tolower((unsigned char)word[j]);
                }
            }

            clean_word[k] = '\0';

            if (k > 0)
            {
                if (insert_word(head, clean_word, file_names[i]) == -1)
                {
                    printf("Memory allocation failed.\n");
                    fclose(fp);
                    return -1;
                }
            }
        }

        fclose(fp);
    }

    printf("Database creation completed.\n");

    return 0;
}

int is_file_present(char *file_name, char *file_names[], int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcmp(file_name, file_names[i]) == 0)
            return 1;
    }

    return 0;
}