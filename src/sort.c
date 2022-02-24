/***********************************************************************/
/* SORTX - Extended Sort. Uses homegrown btree to sort a linked        */
/*         list. If linked list required exceeds memory available a    */
/*         sort of that which will fit is done, then the resultant     */
/*         merged at the end.                                          */
/***********************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {void *up; void *less; void *more; char *str; } leaf;


/* Templates */
void TrimEnd(char *string);
void OutputTree(leaf *top, char* filename);


void main (int argc, char *argv[])

  { char     InputFile[81], OutputFile[81];
    char     szString[500];
    int      dir, nchar;
    FILE     *fInput;
    leaf     *top, *next, *last, *newleaf, *thisleaf;


    /* Identify Input Arguments */
    strcpy(InputFile,  argv[1]);
    strcpy(OutputFile, argv[2]);

    /* BUILD THE TREE */

    fInput = fopen( InputFile, "rt" );
    if ( !fInput ) {
      printf( "Error: Opening input file %s.\n",InputFile);
      exit(8);
      }

    top=0;
    last=0;
    while ( fgets( szString, 499, fInput )) {
      TrimEnd(szString);

      /* Find where to put the leaf */
      next=top;
      while (next != 0) {
        last=next;
        if (strcmp(szString, next->str) < 0) { next=next->less; dir='l';}
        else                                 { next=next->more; dir='m';}
        }

      /* New Leaf */
      newleaf = (leaf *) malloc(sizeof(leaf));
      if (newleaf == 0) { printf("Out of Memory\n"); exit(8); }
      newleaf->less=0;
      newleaf->more=0;
      newleaf->str = (char *) malloc(strlen(szString)+1);
      if (newleaf->str == 0) { printf("Out of Memory\n"); exit(8); }
      strcpy(newleaf->str,szString);

      /* Attach it to Tree */
      if (top==0) { top=newleaf; newleaf->up=0; }
      else if (dir=='l') { last->less=newleaf; newleaf->up=last; }
      else               { last->more=newleaf; newleaf->up=last; }

      } /*endwhile*/

    /* Wrap Up */
    fclose(fInput);

    /* WRITE IT OUT IN SORTED ORDER */
    OutputTree(top, OutputFile);

}

/***********************************************************************/
/*  TrimEnd - Remove trailing blanks (and control characters) from a   */
/*            string.                                                  */
/***********************************************************************/
void TrimEnd(char *string)

  { int nchar;

    nchar=strlen(string);

    /* Right Trim */
    while (string[nchar-1] <= ' ' && nchar > 0) --nchar;
    string[nchar]='\0';

    return;
} /* TrimEnd */


/***********************************************************************/
/* OutputTree - Output the B Tree that has been built so far.          */
/***********************************************************************/
void OutputTree(leaf *top, char* filename)

  { FILE   *fOutput;
    leaf   *thisleaf, *next;
    char   buffer[501];


    /* Open Output File */
    fOutput = fopen( filename, "wt" );
    if ( !fOutput ) {
      printf( "Error: Opening output file %s\n", filename );
      exit(8);
      }

    thisleaf=top;
    while ( thisleaf != 0 ) {

      /* Drill down as far as possible on the left (less) hand side */
      while ( thisleaf->less != 0 ) thisleaf = thisleaf->less;

      /* Consume the value at this point */
      if (thisleaf->str != 0) {
        strcpy(buffer, thisleaf->str);
        strcat(buffer, "\n");
        if ( fputs(buffer, fOutput) == EOF ) {
          printf( "Error: Writing Output Stream.\n" );
          exit(8);
          }
        free(thisleaf->str);
        thisleaf->str=0;
        }

      /* Decide whether to go right or up */
      if (thisleaf->more != 0) {
        /* Go right */
        thisleaf=thisleaf->more;
        }
      else {
        /* Go up */
        /* Confirm that less and str are both zero, else bug */
        if (thisleaf->less != 0 || thisleaf->str != 0) {
          printf("!!bug!!\n"); exit(16); }
        next=thisleaf->up;
        if (next == 0) break; /* Terminating Condition */
        /* Work out whether backtracking a left or right branch */
        if      (next->less == thisleaf) next->less=0;
        else if (next->more == thisleaf) next->more=0;
        else { printf("!!bug!!\n"); exit(16); }
        free(thisleaf);
        thisleaf=next;
        }

      } /*endwhile*/

    /* Wrap Up */
    fclose(fOutput);

}