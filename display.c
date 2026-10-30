
#include "inverted_search.h"

void display_database(main_node *head[])
{
    int i;

    printf("\n========== INVERTED DATABASE ==========\n");

    for (i = 0; i < SIZE; i++)
    {
        main_node *temp = head[i];

        while (temp != NULL)
        {
            printf("\nWord: %s\n", temp->word);
            printf("File count: %d\n", temp->file_count);

            sub_node *sub = temp->sub_link;

            while (sub != NULL)
            {
                printf("File: %s | Word count: %d\n",
                       sub->file_name,
                       sub->word_count);

                sub = sub->link;
            }

            temp = temp->link;
        }
    }

    printf("\n=======================================\n");
}