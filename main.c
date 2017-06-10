#include "binTransl.h"
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char** argv)
{
    double ins1[] = {FLAG_FUNC, IN, CALL, 7, MUL, OUT, END, PUSH, 1, JE, 21, POPR_BX, POPR_AX, PUSHR_AX, PUSHR_AX, PUSH, 1, SUB, CALL, 7, MUL, RET, END};
   /* FILE* ptr  = fopen ("factorial", "wb");
    if (ptr == NULL)
    {
        printf ("huy\n");
        return 1;
    }
    fwrite (ins1, sizeof (double), 23, ptr); */

   /* if (argc < 3)
    {
        fprintf (stderr, "Wrong arguments\n");
        return 1;
    }

    double* buf = fileInBuf_b (argv[1]);
    if (buf == NULL)
    {
        fprintf (stderr, "Can't load file in buffer\n");
        return 1;
    }
    if  (binTransl (buf, creatBinFile (argv[2])))
    {
        fprintf (stderr, "can't transl file\n");
        return 1;
    }
    free (buf);*/
    double* buf1 = fileInBuf_b ("factorial");
    if (buf1 == NULL)
    {
        printf ("fuck null\n");
        return 1;
    }
    char buf[1000000] = {};
    double ins[]  = { PUSHR_AX, PUSHR_BX, IN, PUSH, -5, OUT, PUSHR_CX,  PUSHR_DX, JE, 0, END};
    int i = 0;
   /* double* code  = (double*) calloc (100000, sizeof (double));
    if (code == NULL)
    {
        printf ("ERRROR\n");
        return 1;
    }

    for (i = 0; i < ; i++)
    {*/

    printf ("tr = %d\n", binTransl (buf1, buf, 0, 0));
    printf ("%s\n", buf);
    FILE* ptr = creatBinFile ("test5");
    if (ptr == NULL)
    {
        printf ("hyu\n");
        return 1;
    }
    bufInFile (buf, ptr);
    return 0;
}

