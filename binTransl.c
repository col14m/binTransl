#include "binTransl.h"
#include <assert.h>
#include <stdlib.h>

double* fileInBuf_b (char* file) 
{
    if (file == NULL)
        return NULL;
    struct stat info;
    if (stat (file, &info) == -1) 
        return NULL;
    size_t size = info.st_size;
    FILE* ptrFile = fopen (file, "rb");
    if (ptrFile == NULL)
        return NULL;
    double* buffer = (double*) calloc (size, sizeof (char));
    if (buffer == NULL)
        return NULL;
    if ((fread (buffer, sizeof (double), size / sizeof (double), ptrFile)) != (size / sizeof (double)))
    {
        return NULL;
    }
    fclose (ptrFile);
    return buffer;
}

FILE* creatFileAsm (char* file)
{
    if (!nameIsOk (file))
    {
        return NULL;
    }
    
    FILE* ptrFile = fopen (file, "w");
    if (ptrFile == NULL)
    {
        return NULL;
    }
    fprintf (ptrFile, INIT_TEXT);
    return ptrFile;
}

int nameIsOk (char* name)
{
    if (name == NULL)
    {
        return 0;
    }

    size_t nameLen = strnlen (name, MAX_LEN);
    if (strncmp (".asm", name + nameLen - 4, 4))//need to compare extensions
    {
        return 0;
    }

    return 1;

}

/*int creatAndMakeListing (char* file, const double* binCod)
{
                             
    if (file == NULL || binCod == NULL)
    {
        return NULL_PTR_ERR;
    }
    pid_t result = 0;
    char* nasmAgrs[] = { "nasm",
                         "-g",
                         "-f elf64",
                         file, 
                         "-l test.list",
                         NULL };

    result = fork ();
    if (result == -1)
    {
        return FORK_ERR;
    }
    if (result == 0)
    {
        execve ("/usr/bin/nasm", nasmAgrs, NULL);
        return EXEC_ERR;
    }
    else
    {
        FILE* ptrFile = creatFileAsm (file);
        if (ptrFile == NULL)
        {
            return CREAT_FILE_ERR;
        }
        if (tranlsInText (ptrFile, binCod))
        {
            return TRNSL_ERR;
        }
    }
    return 0;

}*/


//-------------------------------------------------------------------
//------------------Starting BinTrsnl--------------------------------


int binTransl (double* binCode, char* buf, size_t byteCount, size_t progCount)
{
    if (binCode == NULL || buf == NULL)
    {
        return NULL_PTR_ERR;
    }
    #define DEF_CMD(name, code) if (binCode[progCount] == name)\
                                        {\
                                            memcpy (buf + byteCount, code, LENGTH_STRING(code));\
                                            byteCount += LENGTH_STRING(code);\
                                        }\
                                        else
    #define DEF_CMD_JMP(name, code) if (binCode[progCount] == name)\
                                        {\
                                            memcpy (buf + byteCount, code, LENGTH_STRING(code));\
                                            byteCount += LENGTH_STRING(code);\
                                            progCount++;\
                                            int offsetJmp = getOffsetForJmp (progCount, binCode);\
                                            char* change = (char*) &offsetJmp;\
                                            memcpy (buf + byteCount, change, 4);\
                                            byteCount += 4;\
                                        }\
                                        else
    while (binCode[progCount] != END)
    {
        #include "binInstrN.h"
        if (binCode[progCount] == IN)
        {
            binTrnIN (buf, &byteCount);
        }
        else if (binCode[progCount] == OUT)
        {
            binTrnOUT (buf, &byteCount);
        }
        else if (binCode[progCount] == PUSH)
        {
             PUSH_NUMBER;
        }
        else if (binCode[progCount] == FLAG_FUNC)
        {
        
        }
        else
        {
            return UNKNOWN_INSTR_ERR;
        }
        progCount++;
    }
    #undef DEF_CMD
    #undef DEF_CMD_JMP
    memcpy (buf + byteCount, BYTE_COM_EXIT, LENGTH_STRING(BYTE_COM_EXIT));
    byteCount += LENGTH_STRING(BYTE_COM_EXIT); 
    if (binCode[0] == FLAG_FUNC)
    {
        binCode[0] = FLAG_ABSENCE_FUNC; 
        progCount++;
        if (binTransl (binCode, buf, byteCount, progCount))
        {
            return UNKNOWN_INSTR_ERR;
        }
    }
    return 0;
}

int bufInFile (char* buf, FILE* file)
{
    if (buf == NULL || file == NULL)
    {
        return NULL_PTR_ERR;
    }
    fseek (file, OFFSET_START, SEEK_SET); 
    fwrite (buf, sizeof (char), SIZE_BUF, file);
    return 0;
}

FILE* creatBinFile (char* name)
{
    if (name == NULL)
    {
        return NULL;
    }
    
    struct stat info;
    if (stat ("template", &info) == -1) 
    {
        return NULL;
    }
    size_t size = info.st_size;

    FILE* ptrSrc = fopen ("template", "rb");
    FILE* ptrDest = fopen (name, "wb");
    if (ptrSrc == NULL || ptrDest == NULL)
    {
        return NULL;
    }
    
    char* buffer = (char*) calloc (size, sizeof (char));
    if (buffer == NULL)
    {
        return NULL;
    }
    if ((fread (buffer, sizeof (char), size, ptrSrc)) != size)
    {
        return NULL;
    }
    
    
    if ((fwrite (buffer, sizeof (char), size, ptrDest)) != size)
    {
        return NULL;
    }
    
    fclose (ptrSrc);
    
    return ptrDest;

}

int binTrnIN (char* buf, size_t* byteCount)
{
    if (buf == NULL || byteCount == NULL)
    {
        return NULL_PTR_ERR;
    }
    memcpy (buf + *(byteCount), BYTE_COM_IN_BEGIN, LENGTH_STRING(BYTE_COM_IN_BEGIN));
    (*byteCount) += LENGTH_STRING(BYTE_COM_IN_BEGIN) + SIZE_ADDRESS;
    int offset = OFFSET_IN - OFFSET_START - *byteCount;
    char* change = (char*) &offset;
    memcpy (buf + *(byteCount) - SIZE_ADDRESS, change, SIZE_ADDRESS);
    memcpy (buf + *(byteCount), BYTE_COM_IN_END, LENGTH_STRING(BYTE_COM_IN_END));
    (*byteCount) += LENGTH_STRING(BYTE_COM_IN_END);

    return 0;
}


int binTrnOUT (char* buf, size_t* byteCount)
{
    if (buf == NULL || byteCount == NULL)
    {
        return NULL_PTR_ERR;
    }
    memcpy (buf + *(byteCount), BYTE_COM_OUT_BEGIN, LENGTH_STRING(BYTE_COM_OUT_BEGIN));
    (*byteCount) += LENGTH_STRING(BYTE_COM_OUT_BEGIN) + SIZE_ADDRESS;
    int offset = OFFSET_OUT - OFFSET_START - *byteCount;
    char* change = (char*) &offset;
    memcpy (buf + *(byteCount) - SIZE_ADDRESS, change, SIZE_ADDRESS);
    memcpy (buf + *(byteCount), BYTE_COM_OUT_END, LENGTH_STRING(BYTE_COM_OUT_END));
    (*byteCount) += LENGTH_STRING(BYTE_COM_OUT_END);

    return 0;

}


int getOffsetForJmp (size_t progCount_t, const double* binCod)
{
    if (binCod == NULL)
    {
        return NULL_PTR_ERR;
    }
    assert (progCount_t < 2500);
    int progCount = (int) progCount_t;
    int address = binCod[progCount];
    if (address < progCount)
    {
        int byteCount = 0;
        int end = progCount;
        #define DEF_CMD_J(name, numByte) if (binCod[address] == name)\
                                                     {\
                                                         byteCount += numByte;\
                                                     }\
                                                     else
        #define DEF_CMD_JTWO(name, numByte) if (binCod[address] == name)\
                                                     {\
                                                         byteCount += numByte;\
                                                         address++;\
                                                     }\
                                                     else



        for (address = binCod[progCount]; address <= end; address++)
        {
            #include "numBytes.h"
            if (binCod[address] == PUSH)
            {
                byteCount += NUM_BYTES_PUSH_NUM;
                address++;
            }
            else
            {
                byteCount += NUM_BYTES_NUM;
            }
        }
        #undef DEF_CMD_J
        #undef DEF_CMD_JTWO

        return -byteCount;
    }
    else if (address > progCount)
    {
        int byteCount = 0;
        progCount++;
        #define DEF_CMD_J(name, numByte) if (binCod[progCount] == name)\
                                                     {\
                                                         byteCount += numByte;\
                                                     }\
                                                     else
        #define DEF_CMD_JTWO(name, numByte) if (binCod[progCount] == name)\
                                                     {\
                                                         byteCount += numByte;\
                                                         progCount++;\
                                                     }\
                                                     else


        for (progCount; progCount < address; progCount++)
        {
            #include "numBytes.h"
            if (binCod[progCount] == PUSH)
            {
                byteCount += NUM_BYTES_PUSH_NUM;
                progCount++;
            }
            else
            {
                byteCount += NUM_BYTES_NUM;
            }
        }
        #undef DEF_CMD_J
        #undef DEF_CMD_JTWO

        return byteCount;
    }

    return UNKNOWN_INSTR_ERR;
}



