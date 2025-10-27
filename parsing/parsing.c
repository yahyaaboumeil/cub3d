#include "parsing.h"



char **parsing(char *file_name)
{
   int fd;

   fd = 0;
   if (!check_file(file_name))
   {
        printf("\nfile name is't correct\n");
        return NULL;
   }
   fd = open_file(file_name, fd);
   if (fd == -1)
      return (printf("\nError\nCannot open file\n"), NULL);
   char **lines = diretion_pasing(fd); 
   if (!lines)
   {
      printf("\nthe 4 lines is't good\n");
      return NULL;
   }
   printf("\nthe 4 lines is good\n");
   lines = color_parsing(lines, fd);
   if (!lines)
   {
      printf("\nthe 2 color lines is't good\n");
      return NULL;
   }
   printf("\nthe 2 color lines is good\n");
   
   lines  = check_input(fd, lines);
   free_memory(lines);
   free_getline(fd);
   return NULL;
}
