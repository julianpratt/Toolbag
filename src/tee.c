/* tee.c                                                              */
/* a program to read standard in and write to standard out and a file */
/* thus duplicating the input                                         */

#include <stdio.h>
#include <stdlib.h>

int main(argc,argv)
int argc;
char *argv[];
{
 int rc=0 ;
 int inchar ;
 FILE *outfp ;

 if ( argc != 2 )
 {
  fprintf(stderr , "Usage:    tee  output_file_name\n") ;
  exit(1) ;
}
if ( ( outfp = fopen(argv[1] , "a+t" )) == NULL )
{
  fprintf(stderr , "Failed to open output file %s\n" , argv[1]) ;
  exit(1) ;
}

while ( (inchar = getchar()) != EOF )
{
  putchar(inchar) ;
  putc(inchar , outfp) ;
}

return rc ;
}