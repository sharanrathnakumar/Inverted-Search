#include "inverted_index.h"

int main(int argc, char *argv[])
{
    // Validation  and storing part
    file_node_t *file_f_head = NULL;
    if (argc <= 1)        
        printf("Erorr: Please enter parameters\nUsage : ./a.out file1.txt");
    else
    {
        validate_n_store_filenames(&file_f_head, argv);
    }
}

void validate_n_store_filenames(file_node_t **file_f_head, char *filenames[])
{
    for (int i = 1; filenames[i] != NULL; i++)
    {
        int ret = IsFileValid(filenames[i]);
        if (ret == SUCCESS)
        {
            ret = store_filenames_to_list(filenames[i], file_f_head);
            if (ret == REPEATED)
                printf("Error: Filename is repeated\n");
            else
            {
                main_node_t *main_array[26] = {NULL}; // Array of structer pointers is Initialised as NULL
                char option = 'y';
                while (option == 'y' || option == 'Y')
                {
                    int num = display();
                    switch (num)
                    {
                    case 1:
                        if(create_DB(*file_f_head, main_array) == SUCCESS)
                        printf("Data Base Created\n");
                        break;
                    case 2:
                        display_DB(main_array);
                        break;
                    case 3:
                        char word[NAMELENGTH];
                        printf("Enter the word you want to search: \n");
                        scanf("%s", word);
                       // search_DB(main_array, word);
                        break;
                    case 4:
                        char filename[NAMELENGTH];
                        printf("Enter the filename: \n");
                        scanf("%s", filename);
                      //  if (update_DB(file_f_head, main_array, filename) == SUCCESS)
                            printf("Database Updated\n");
                      //  else
                            printf("Not Updated\n");
                        break;
                    default:
                        printf("Invalid Choice");
                        break;
                    }
                    printf("Do Yo Wish To Continue ? (y/n)\n");
                    scanf(" %c", &option);
                }
            }
        }
        else if (ret == NOT_PRESENT)
            printf("Error: File not Found\n");
        else
            printf("Error: Empty File\n");
    }
}

int display()
{
    int num;
    printf("1. Create Database\n2.Display Database\n3.Update Database\n4.Search Database\n5.Save Database\n");
    scanf("%d", &num);
    return num;
}