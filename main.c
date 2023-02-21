#include "inverted_index.h"

int main(int argc, char *argv[])
{
    // Validation  and storing part
    file_node_t *file_f_head = NULL;
    if (argc <= 1)
    {
        red();
        printf("Error: Please enter parameters\nUsage : ./a.out file1.txt\n");
        reset();
    }
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
            {
                red();
                printf("Error: Filename is repeated\n");
                reset();
            }
            else
            {
                main_node_t *main_array[26] = {NULL}; // Array of structer pointers is Initialised as NULL
                char option = 'y';
                while (option == 'y' || option == 'Y')
                {
                    int num = display();
                    reset();
                    switch (num)
                    {
                    case 1:
                        if (create_DB(*file_f_head, main_array) == SUCCESS){
                            green();
                            printf("Data Base Created\n");
                            reset();
                        }
                        break;
                    case 2:
                        display_DB(main_array);
                        break;
                    case 3:
                        char word[NAMELENGTH];
                        printf("Enter the word you want to search: \n");
                        scanf("%s", word);
                        if (search_DB(main_array, word) == NOT_PRESENT)
                            printf("The word %s is not present\n", word);
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
                    case 5:
                        char fname[NAMELENGTH];
                        printf("Enter filename to save your Backup : ");
                        scanf("%s", fname);
                        save_DB(main_array, fname);
                        break;
                    default:
                        printf("Invalid Choice");
                        break;
                    }
                    printf("\nDo Yo Wish To Continue (y/n) : ");
                    scanf(" %c", &option);
                    if(option == 'n' || option == 'N')
                    printf("\n---------Exit--------\n");
                    else
                    printf("Invalid Choice Exiting\n");
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
    green();
    printf("1. Create Database\n2.Display Database\n3.Search Database\n4.Update Database\n5.Save Database\n");
    scanf("%d", &num);
    if(num >= 1 && num <=5)
    return num;
    else
    {
        printf("\nInvalid Input\nPlease enter a number between (1-5)\n\n");
        display();
    }
}


/*Color*/
void red()
{
    printf("\033[0;31m");
}
void green()
{
    printf("\033[0;32m");
}

void reset()
{
    printf("\033[0m");
}