#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>


#define MAX_LEN 100

#define INIT_TEXT "global _start\n\
extern printf\n\
extern scanf\n\
section .data\n\
val: dd 0.0      \n\
formatPrint  db \'%%lg\', 10, 0\n\
formatScan  db \'%%lg\',0\n\
section .text\n\
_start:\n\
finit\n"


#define PUSH_NUMBER progCount++;\
                    float convert = (float) binCode[progCount];\
                    char* change = (char*) &convert;\
                    memcpy (buf + byteCount, BYTE_COM_PUSH_BEGIN, sizeof (BYTE_COM_PUSH_BEGIN) - 1);\
                    byteCount += sizeof (BYTE_COM_PUSH_BEGIN) - 1;\
                    memcpy (buf + byteCount, change, 4);\
                    byteCount += 4;\
                    memcpy (buf + byteCount, BYTE_COM_PUSH_END, sizeof (BYTE_COM_PUSH_END));\
                    byteCount += sizeof (BYTE_COM_PUSH_END) - 1;\


#define ADDRESS_TMP_VAR  "\x28\x10\x60\x00"

#define BYTE_COM_JMP    "\xD8\xD1"/*fcom st(1)*/\
                        "\x9B"/*wait*/\
                        "\xDF\xE0"/*fnstsw ax*/\
                        "\x9B"/*wait*/\
                        "\x9E"/*sahf*/\
                        "\x0F"/*jmp:je, jne, jbe...*/

#define FLD_TMP_VAR  "\xD9\x04\x25" /*fld dword [ADDRESS_TMP_VAR]*/
#define FST_TMP_VAR  "\xD9\x1C\x25" /*fstp dword [ADDRESS_TMP_VAR]*/

#define BYTE_COM_IN_BEGIN   "\x41\x52"/*push r10*/\
                            "\xE8"/*call*/

#define BYTE_COM_IN_END     "\x41\x5A"/*pop r10*/



#define BYTE_COM_OUT_BEGIN  "\x41\x52"/*push r10*/\
                            "\x53"/*push rbx*/\
                            "\x51"/*push rcx*/\
                            "\x52"/*push rdx*/\
                            "\xE8"/*call*/

#define BYTE_COM_OUT_END    "\x5A"/*pop rdx*/\
                            "\x59"/*pop rcx*/\
                            "\x5B"/*pop rbx*/\
                            "\x41\x5A"/*pop r10*/



#define BYTE_COM_PUSH_BEGIN "\xC7\x04\x25" ADDRESS_TMP_VAR /*mov [ADDRESS_TMP_VAR], num*/
       
#define BYTE_COM_PUSH_END "\xD9\x04\x25" ADDRESS_TMP_VAR /*fld [ADDRESS_TMP_VAR]*/
       
#define BYTE_COM_EXIT   "\xB8\x3C\x00\x00\x00" /*mov eax, 0x3C*/\
                        "\xBF\x00\x00\x00\x00" /*mov edi, 0*/\
                        "\x0F\x05" /*syscall*/

#define LENGTH_STRING(string) sizeof (string) - 1

#define SIZE_BUF 1800

#define SIZE_ADDRESS 4

double* fileInBuf_b (char* file);

int nameIsOk (char* name);

FILE* creatFileAsm (char* name);

//int tranlsInText (FILE* asmFile, const double* binCod);

//int creatAndMakeListing (char* file, const double* binCod);

int binTransl (double* binCode, char* buf, size_t byteCount, size_t progCount);

FILE* creatBinFile (char* name);

int getOffsetForJmp (size_t progCount, const double* binCod);

int binTrnIN (char* buf, size_t* byteCount);

int binTrnOUT (char* buf, size_t* byteCount);

int binTrnFunc (FILE* file, size_t byteCount, double* binCode, size_t progCount);

int bufInFile (char* buf, FILE* file);

enum Type
{
	PUSH = 25,
	POP = 11,
	ADD = 12,
	SUB = 13,
	MUL = 14,
	DIV = 15,
	SQRT = 16,
	PUSHR_AX = 31,
	PUSHR_BX = 32,
	PUSHR_CX = 33,
	PUSHR_DX = 34,
	POPR_AX = 35,
	POPR_BX = 36,
	POPR_CX = 37,
	POPR_DX = 38,
	PUSHR = 17,
	POPR = 18,
	JE = 19,
	JNE = 20,
	JA = 21,
	JAE = 22,
	JB = 23,
	JBE = 24,
	SIN = 10,
	END = 9,
	IN = 8,
	OUT = 7,
    CALL = 6,
    RET = 5,
    FLAG_FUNC = 1,
    FLAG_ABSENCE_FUNC = 0

};

enum Errors
{
    NAME_ERR = 1,
    NULL_PTR_ERR = 2,
    UNKNOWN_INSTR_ERR = 3,
    CREAT_FILE_ERR = 4,
    TRNSL_ERR = 5,
    FORK_ERR = 6,
    EXEC_ERR = 7
};

enum Offsets
{
    OFFSET_START = 800,
    OFFSET_IN = 2848,
    OFFSET_OUT = 2927
};

enum numBytes
{
    NUM_BYTES_IN_BEF = 7,
    NUM_BYTES_IN_AFT = 2,
    NUM_BYTES_OUT_BEF = 10,
    NUM_BYTES_OUT_AFT = 5,
    NUM_BYTES_PUSH_NUM = 18,
    NUM_BYTES_NUM = 4
};

