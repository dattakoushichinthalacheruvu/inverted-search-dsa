
#include "inverted_search.h"

int save_database(main_node *head[], char file_name[])
{
    FILE *fp = fopen(file_name, "w");

    if (fp == NULL)
    {
        return -1;
    }

    int i;

    for (i = 0; i < SIZE; i++)
    {
        main_node *temp = head[i];

        while (temp != NULL)
        {
            fprintf(fp, "%s %d",
                    temp->word, temp->file_count);

            sub_node *sub = temp->sub_link;

            while (sub != NULL)
            {
                fprintf(fp, " %s %d",
                        sub->file_name,
                        sub->word_count);

                sub = sub->link;
            }

            fprintf(fp, "\n");

            temp = temp->link;
        }
    }

    fclose(fp);

    return 0;
}

int load_database(main_node *head[], char file_name[])
{
    FILE *fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("Cannot open saved database.\n");
        return -1;
    }

    char word[WORD_SIZE];
    char filename[FILE_SIZE];
    int file_count;
    int word_count;

    while (fscanf(fp, "%49s %d", word, &file_count) == 2)
    {
        int i;

        for (i = 0; i < file_count; i++)
        {
            if (fscanf(fp, "%99s %d",
                       filename, &word_count) != 2)
            {
                fclose(fp);
                return -1;
            }

            int index = hash_function(word);

            main_node *temp = head[index];

            while (temp != NULL &&
                   strcmp(temp->word, word) != 0)
            {
                temp = temp->link;
            }

            if (temp == NULL)
            {
                main_node *new_main =
                    malloc(sizeof(main_node));

                if (new_main == NULL)
                {
                    fclose(fp);
                    return -1;
                }

                strcpy(new_main->word, word);
                new_main->file_count = 0;
                new_main->sub_link = NULL;
                new_main->link = head[index];

                head[index] = new_main;
                temp = new_main;
            }

            sub_node *sub = temp->sub_link;

            while (sub != NULL &&
                   strcmp(sub->file_name, filename) != 0)
            {
                sub = sub->link;
            }

            if (sub == NULL)
            {
                sub_node *new_sub =
                    malloc(sizeof(sub_node));

                if (new_sub == NULL)
                {
                    fclose(fp);
                    return -1;
                }

                strcpy(new_sub->file_name, filename);
                new_sub->word_count = word_count;
                new_sub->link = temp->sub_link;

                temp->sub_link = new_sub;
                temp->file_count++;
            }
            else
            {
                sub->word_count = word_count;
            }
        }
    }

    fclose(fp);

    return 0;
}

void free_database(main_node *head[])
{
    int i;

    for (i = 0; i < SIZE; i++)
    {
        main_node *temp = head[i];

        while (temp != NULL)
        {
            sub_node *sub = temp->sub_link;

            while (sub != NULL)
            {
                sub_node *temp_sub = sub;
                sub = sub->link;
                free(temp_sub);
            }

            main_node *temp_main = temp;
            temp = temp->link;

            free(temp_main);
        }

        head[i] = NULL;
    }
}