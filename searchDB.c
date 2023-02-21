#include "inverted_index.h"
int search_DB(main_node_t *main_array[], char *word)
{
    int index = toupper(word[0]) % 65,flag=0;
    main_node_t *ptr = main_array[index];
    while(ptr != NULL)
    {
        if(!strcmp(ptr->word,word))
        {
            flag=1;
            printf("The word %s is present in %d file(s)\n",ptr->word, ptr->f_count);
            sub_node_t *sptr= ptr->sub_link;
            while(sptr != NULL)
            {
                printf("In file %s %d time(s)\n",sptr->f_name,sptr->w_count);
                sptr = sptr->link;
            }
        }
        ptr= ptr->link;
    }
    if(flag == 0)
    return NOT_PRESENT;
}