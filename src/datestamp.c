/***********************************************************************/
/*                                                                     */
/*  DATESTAMP - Output a 8 character date stamp.                       */
/*                                                                     */
/*  Usage:  DATER                                                      */
/*                                                                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main ( void )

  { time_t system_time;
    struct tm *tblk;


    /* Determine Day of Month and Day of Week based System Date */
    system_time=time(NULL);
    tblk=localtime(&system_time);

    /* Set the Environmental Variable */
    printf("%02d%02d%04d",tblk->tm_mday,tblk->tm_mon+1,tblk->tm_year+1900);

    return 0;
} /* Main */