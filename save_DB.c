#include "inverted_index.h"

int save_DB(main_node_t *main_array[], char *fname)
{
    int index;
    FILE *fptr = fopen(fname, "w");
    if (fptr == NULL)
        return FAILURE;

    main_node_t *ptr;
    sub_node_t *sptr;
    for (index = 0; index < 26; index++)
    {

        ptr = main_array[index];
        if (ptr != NULL)
        {
            fprintf(fptr, "#%d;\n", index);
            while (ptr != NULL)
            {
                sptr = ptr->sub_link;
                fprintf(fptr,"%s; %d",ptr->word, ptr->f_count);
                while (sptr != NULL)
                {
                    fprintf(fptr, "; %s ; %d",sptr->f_name, sptr->w_count);
                    sptr = sptr->link;
                }
                fprintf(fptr,"%s","#\n");
                ptr =ptr->link;
            }
        }
    }
}