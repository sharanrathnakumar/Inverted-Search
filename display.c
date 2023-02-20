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
            printf("Index[%d] : ", i);
            while (ptr != NULL)
            {
                printf("-> %s ", ptr->word);
                ptr = ptr->link;
            }
            printf("\n");
        }
    }
}