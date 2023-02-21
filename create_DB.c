#include "inverted_index.h"

/*Creating Data Base*/

int create_DB(file_node_t *file_f_head, main_node_t *main_array[])
{
    main_node_t *new = malloc(sizeof(main_node_t));
    while (file_f_head != NULL) // Iterates untill file_node table link is NULL
    {
        read_datafile(main_array, file_f_head->f_name); // Reads data from file repeatedly
        file_f_head = file_f_head->link;                // Points to next filename pointer
    }

    return SUCCESS;
}

void read_datafile(main_node_t *main_array[], char *f_name)
{
    FILE *fptr = fopen(f_name, "r");      // File pointer Initialized
    char word[NAMELENGTH];                // character array to store words
    while (fscanf(fptr, "%s", word) == 1) // Scans word seperated by space and store in word array
    {
        //  printf("%s\n", word);
        insert_at_last_main(main_array, word, f_name); // Calling Insert at last function
    }
}

int insert_at_last_main(main_node_t *main_array[], char *word, char *f_name)
{
    int index = toupper(word[0]) % 65; // Find the index of word to be added
   // printf("Index: %d\nWord: %s\n", index, word);

    // If array of index is NULL create a new main_node table
    if (main_array[index] == NULL)
    {
        main_array[index] = create_main_node(word, f_name);
        return SUCCESS;
    }
    // If the main_array[index] is not NULL
    // Checking whether entered word is in main_node table
    if (check_n_update(main_array, word, f_name) == SUCCESS)
    {
        return SUCCESS;
       // printf("Main Updated\n");
    }
}

main_node_t *create_main_node(char *word, char *f_name)
{
    main_node_t *new = malloc(sizeof(main_node_t));
    new->f_count = 1;
    new->link = NULL;
    strcpy(new->word, word);
    new->sub_link = create_sub_node(word, f_name);
    return new;
}

sub_node_t *create_sub_node(char *word, char *f_name)
{
    sub_node_t *newSub = malloc(sizeof(sub_node_t));
    strcpy(newSub->f_name, f_name);
    newSub->link = NULL;
    newSub->w_count = 1;
    return newSub;
}

int check_n_update(main_node_t *main_array[], char *word, char *f_name)
{
    int index = toupper(word[0]) % 65;
    main_node_t *ptr = main_array[index], *prev;
    while (ptr != NULL)
    {
        if (!strcmp(ptr->word, word))
        {
            // Update the sub node part
            int ret = check_sub_node(ptr->sub_link, f_name);
            if (ret == SUCCESS)
                return SUCCESS;
            else if (ret = NOT_PRESENT)
            {
                sub_node_t *temp = ptr->sub_link;
                ptr->f_count++;
                while(temp->link != NULL)
                {
                    temp = temp->link;
                }
                temp->link = create_sub_node(word, f_name);
                return SUCCESS;
            }
        }
        prev = ptr;
        ptr = ptr->link;
    }
    prev->link = create_main_node(word, f_name);
    return SUCCESS;
}

// Check and Update Sub Node
int check_sub_node(sub_node_t *ptr, char *f_name)
{
    sub_node_t *temp = ptr;
    while (temp != NULL)
    {
        if (!strcmp(ptr->f_name, f_name))
        {
            printf("%d", ptr->w_count++);
            return SUCCESS;
        }
        temp = temp->link;
    }
    return NOT_PRESENT;
}

