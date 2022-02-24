/**********************************************************************/
/* CHANGE - Filter to alter one character in the stream to one or     */
/*          more others. Arguments are From and To, where From is     */
/*          specified as a 2 digit hex number (the character to be    */
/*          changed), and To is 0 or multiples of 2 digit hex numbers */
/*          that this character is to be changed into.                */
/*          File is read from stdin and written to stdout.            */
/**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main( int argc, char *argv[])
{
    char    From, in, *To, *ptemp, temp[3], *ptemp2;
    int     nchar, i;
    unsigned long ult;

    /* Get Command Line Arguments */
    if ( argc <  1 ) {       /* Wrong number of arguments */
      printf("CHANGE - Filter to alter one character in the stream to one or\n");
      printf("         more others. Arguments are From and To, where From is\n");
      printf("         specified as a 2 digit hex number (the character to be\n");
      printf("         changed), and To is 0 or multiples of 2 digit hex numbers\n");
      printf("         that this character is to be changed into.\n");
      printf("         File is read from stdin and written to stdout.\n");
      printf("\n");
      printf("Usage: CHANGE from (to)\n");
      printf(" \n");
      }

    /* Interpret the Arguments */
    ult=strtoul(argv[1], &ptemp, 16);
    From=ult;
    nchar=strlen(argv[2])/2;
    ptemp=argv[2];
    To=malloc(nchar+1);
    if (To==0) exit(8);
    for (i=0; i<nchar; ++i) {
      strncpy(temp,ptemp+i*2,2);
      temp[2]='\0';
      ult=strtoul(temp, &ptemp2, 16);
      To[i]=ult;
      }
    To[nchar]='\0';

    /* Read stdio */
    while ( (in=getc(stdin)) != EOF ) {
      if (in == From) for (i=0; To[i]!=0; ++i) putc(To[i], stdout);
      else putc(in, stdout);
      }

}
