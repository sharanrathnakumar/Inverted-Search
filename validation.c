#include "inverted_index.h"

int IsFileValid(char *filename)
{
    FILE *fptr;
    long size;
    // printf("%s\n", filename);
    fptr = fopen(filename, "r");
    if (fptr == NULL)
        return NOT_PRESENT;

    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);
    if (size == 0)
        return FILE_EMPTY;
    else
        return SUCCESS;
}

int store_filenames_to_list(char *filename, file_node_t **file_f_head)
{
    file_node_t *new = malloc(sizeof(file_node_t)); // Allocating memory to struct pointer new to add file name
    strcpy(new->f_name, filename);
    new->link = NULL;
    if (*file_f_head == NULL) // If file head is empty update head address with new address
    {
        *file_f_head = new;
        return SUCCESS;
    }
    file_node_t *ptr = *file_f_head, *prev;
    while (ptr != NULL)
    {
        prev = ptr;
        if (!strcmp(ptr->f_name, new->f_name)) // Checking if new file name is same as old filename
            return REPEATED;                   // If yes returns repeated
        ptr = ptr->link;                       // updating pointer to next node untill ptr = NULL
    }
    prev->link = new; // If name is not repeated update the link of prev with new address
    return SUCCESS;   // return SUCCESS
}
