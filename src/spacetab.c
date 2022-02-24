// Created by Patrick O'Byrne
// Started on 2/12/93
//
// This application takes an input text file and converts tabs to a desired
// number of spaces.
// If tabs and spaces have been intermixed, the number of spaces for each
// tab should be chosen to be the same as that used when the file was built.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <fcntl.h>
#include <unistd.h> 


int OpenFiles(void);
void CloseFiles(void);
int ConvertFile(void);


int         nInFH;              // input file handle
int         nOutFH;             // output file handle
char        szIn[15];           // input file name
char        szOut[15];          // output file name
int         nSpaces;            // number of spaces replacer
char        *pSpaceBuff;        // tab replacer



//	FUNCTION    main
//
//  DESC        controls the program flow
//
//  I/P PARAMS  char			*argv[1]		the file name to work with
//
//  O/P PARAMS  none
//
//  RETURN      none
//
void main (int argc, char *argv[], char *envp[])
{
int         nRet;                               // function return value

    // read the input file name
    if (argc != 4)
    {
        printf("You must call with an input file, output file and spaces\n");
        exit(1);
    }

    printf("Starting conversion\n");
    strcpy(szIn, argv[1]);
    strcpy(szOut, argv[2]);
    nSpaces = atoi(argv[3]);

    // open the files
    nRet = OpenFiles();

    if (!nRet)
    {
        pSpaceBuff = malloc(nSpaces);
        if (pSpaceBuff)
            memset(pSpaceBuff, ' ', nSpaces);
        else
        {
            printf("Could not allocate memory\n");
            exit(1);
        }
    }
    else exit(1);

    if (!nRet)
        nRet = ConvertFile();

    // tidy up
    CloseFiles();
    if (pSpaceBuff)
        free(pSpaceBuff);

    // display end message
    if (nRet) {
        printf("Conversion aborted\n");
        exit(1);
    }
    else
	    printf("Finished conversion\n");

    return;
}



//	FUNCTION    OpenFiles
//
//  DESC        opens the required files
//
//  I/P PARAMS  none
//
//  O/P PARAMS  none
//
//	RETURN		int             0 if OK
//                              1 on failure
//
int OpenFiles(void)
{
int         nRet = 0;                           // function return

    nInFH = nOutFH = 0;

    // open the input file
    if ((nInFH = open(szIn, O_RDONLY)) == -1)
    {
        printf("Could not open input file\n");
    	nRet = 1;
    }
    else
    {
	    // open the ouput file
 	    if ((nOutFH = open(szOut, O_CREAT|O_TRUNC|O_WRONLY)) == -1)
        {
	        printf("Could not open output file\n");
	    	nRet = 1;
        }
    }

    return (nRet);
}



//	FUNCTION    CloseFiles
//
//  DESC        closes files before shutdown
//
//  I/P PARAMS  none
//
//  O/P PARAMS  none
//
//  RETURN      none
//
void CloseFiles(void)
{
    if (nInFH > 0)
        close(nInFH);
    if (nOutFH > 0)
        close(nOutFH);

    return;
}



//	FUNCTION    ConvertFile
//
//  DESC        reads through the file replacing tabs with spaces
//
//  I/P PARAMS  none
//
//  O/P PARAMS  none
//
//  RETURN      int             0 if OK
//                              1 on failure
//
int ConvertFile(void)
{
int         nRet = 0;                           // function return
char        szBuffer[1];                        // read buffer
int         nCharsSinceCRLF = 0;                // number of characters in
                                                // line so far
int         nMod;                               // modulus for tabbing

    while (!nRet)
    {
	    nRet = read(nInFH, szBuffer, 1);
		if (nRet > -1)
		{
    		if (nRet == 0)
        		break;

	        nRet = 0;

            if (szBuffer[0] == 0x09)
            {
                nMod = nCharsSinceCRLF % nSpaces;
                nMod = nSpaces - nMod;
                write(nOutFH, pSpaceBuff, nMod);
                nCharsSinceCRLF += nMod;
            }
            else
            {
                write(nOutFH, szBuffer, 1);
                nCharsSinceCRLF++;
            }

            if ((szBuffer[0] == 0x0A) || (szBuffer[0] == 0x0D))
                nCharsSinceCRLF = 0;
    	}
        else
            nRet = 1;
	}

    return (nRet);
}
