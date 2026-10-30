
#include "inverted_search.h"

int main(int argc, char *argv[])
{
    main_node *head[SIZE] = {NULL};

    int choice;
    char word[WORD_SIZE];
    char save_file[FILE_SIZE];

    if (argc < 2)
    {
        printf("Usage: ./inverted_search file1.txt file2.txt\n");
        return 1;
    }

    create_database(head, argv + 1, argc - 1);

    while (1)
    {
        printf("\n----- INVERTED SEARCH MENU -----\n");
        printf("1. Create Database\n");
        printf("2. Search Database\n");
        printf("3. Display Database\n");
        printf("4. Save Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input\n");
            break;
        }

        switch (choice)
        {
            case 1:
                printf("Enter text filenames to add (use command line to load files initially).\n");
                printf("Use option 5 to load a saved database.\n");
                break;

            case 2:
                printf("Enter word to search: ");
                scanf("%49s", word);
                search_database(head, word);
                break;

            case 3:
                display_database(head);
                break;

            case 4:
                printf("Enter database filename: ");
                scanf("%99s", save_file);

                if (save_database(head, save_file) == 0)
                    printf("Database saved successfully.\n");
                else
                    printf("Database save failed.\n");
                break;

            case 5:
                printf("Enter saved database filename: ");
                scanf("%99s", save_file);

                if (load_database(head, save_file) == 0)
                    printf("Database loaded successfully.\n");
                else
                    printf("Database loading failed.\n");
                break;

            case 6:
                free_database(head);
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    free_database(head);
    return 0;
}