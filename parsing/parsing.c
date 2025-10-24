#include "parsing.h"



char **parsing(char *file_name)
{
   if (!check_file(file_name))
   {
        printf("\nfile name is't correct\n");
        return NULL;
   }

   if (!diretion_pasing(file_name))
   {
      printf("\nthe 6 lines is't good\n");
      return NULL;
   }
   printf("\nthe 6 lines is good\n");
   return NULL;
}
