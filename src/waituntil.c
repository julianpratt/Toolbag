/***********************************************************************/
/*                                                                     */
/*  WAITUNTL - Wait Until a given time.                                */
/*                                                                     */
/*  Usage:  WAITUNTL time                                              */
/*                                                                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void main (int argc, char *argv[])

  { time_t system_time;
    struct tm *tblk;
    int    hours, mins;

    /* Convert time to Hours and Minutes */
    if (argc != 2 || sscanf(argv[1],"%d:%d",&hours,&mins) != 2 ||
        hours < 0 || hours > 24 || mins < 0 || mins > 60 ) {
      printf("syntax: WAITUNTIL hh:mm\n");
      if (argc == 2 ) printf("        %s is not a valid time\n",argv[1]);
      exit (8);
      }

    /* Determine Day of Month and Day of Week based System Date */
    system_time=time(NULL);
    tblk=localtime(&system_time);

    /* Wait until hour specified */
    while ( ! ( tblk->tm_hour >= hours && tblk->tm_min >= mins ) ) {
      sleep(10);
      system_time=time(NULL);
      tblk=localtime(&system_time);
      printf("%02d:%02d:%02d\n",tblk->tm_hour,tblk->tm_min,tblk->tm_sec);
      }

    return;
} /* Main */