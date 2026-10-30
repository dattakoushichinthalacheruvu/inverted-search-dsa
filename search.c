
#include "inverted_search.h"

int search_database(main_node *head[], char word[])
{
    int index;
    main_node *temp;

    int i;

    for (i = 0; word[i] != '\0'; i++)
    {
        word[i] = tolower((unsigned char)word[i]);
    }

    index = hash_function(word);

    temp = head[index];

    while (temp != NULL)
    {
        if (strcmp(temp->word, word) == 0)
        {
            printf("\nWord found: %s\n", temp->word);
            printf("Files containing the word: %d\n",
                   temp->file_count);

            sub_node *sub = temp->sub_link;

            while (sub != NULL)
            {
                printf("File: %s | Count: %d\n",
                       sub->file_name,
                       sub->word_count);

                sub = sub->link;
            }

            return 0;
        }

        temp = temp->link;
    }

    printf("Word not found in database.\n");

    return -1;
}