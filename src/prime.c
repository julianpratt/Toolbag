/***********************************************************************/
/*                                                                     */
/*  PRIME - Determines the lowest prime factor of a number.            */
/*                                                                     */
/*  Usage:  PRIME n (where n is the number whose prime is required).   */
/*                                                                     */
/***********************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void main (int argc, char *argv[])

  { int n, factor, maxfac;


    if ( argc != 2 ||(n=atoi(argv[1])) <= 0 ) {
      printf("PRIME - Determines the lowest prime factor of a number.\n\n");
      printf("usage: PRIME n (where n is the number whose prime is required).\n");
      exit(0);
      }

    if (n%2==0) {
      printf("Lowest Prime Factor of %d is 2\n",n);
      exit(0);
      }

    maxfac=(int)sqrt((double)n);
    for(factor=3; factor<=maxfac; factor+=2) if (n%factor==0) break;
    if (n%factor==0) printf("Lowest Prime Factor of %d is %d\n",n,factor);
    else             printf("%d is prime\n",n);

} /* Main */