#include "inverted_index.h"

int display_DB(main_node_t *main_array[])
{
    printf("-----------------DATA BASE-------------------\n\n");
    main_node_t *ptr;
    sub_node_t *sptr;
    for (int i = 0; i < 26; i++)
    {
        ptr = main_array[i];
        if (ptr != NULL)
        {
            printf("[%d] : ", i);
            while (ptr != NULL)
            {
                printf(" %s %d file(s)", ptr->word,ptr->f_count);
                sptr = ptr->sub_link;
                while(sptr != NULL)
                {
                    printf(" %s %d ",sptr->f_name, sptr->w_count);
                    sptr = sptr->link;
                }
                ptr = ptr->link;
            }
            printf("\n");
        }
    }
}