DEF_CMD(SQRT, "\xD9\xFA" //fsqrt
                )  
DEF_CMD(ADD, "\xDE\xC1" //fadd
                ) 
DEF_CMD(SUB, "\xDE\xE9" //fsub
                ) 

DEF_CMD(MUL, "\xDE\xC9" //fmul
                )

DEF_CMD(DIV, "\xDE\xF9"//fdiv
                ) 

DEF_CMD(PUSHR_AX,   "\x44\x89\x14\x25" ADDRESS_TMP_VAR //mov [ADDRESS_TMP_VAR], r10
                    FLD_TMP_VAR ADDRESS_TMP_VAR //fld [ADDRESS_TMP_VAR] 
                    )

DEF_CMD(PUSHR_BX,   "\x89\x1C\x25" ADDRESS_TMP_VAR //mov [ADDRESS_TMP_VAR], ebx 
                    FLD_TMP_VAR ADDRESS_TMP_VAR //fld [ADDRESS_TMP_VAR]
                    )

DEF_CMD(PUSHR_CX,   "\x89\x0C\x25" ADDRESS_TMP_VAR //mov [ADDRESS_TMP_VAR], ecx
                    FLD_TMP_VAR ADDRESS_TMP_VAR // fld [ADDRESS_TMP_VAR]
                    )

DEF_CMD(PUSHR_DX,   "\x89\x14\x25" ADDRESS_TMP_VAR //mov [ADDRESS_TMP_VAR], edx
                    FLD_TMP_VAR ADDRESS_TMP_VAR // fld [ADDRESS_TMP_VAR]
                    )

DEF_CMD(POPR_AX,    FST_TMP_VAR ADDRESS_TMP_VAR // fstp [ADDRESS_TMP_VAR]
                    "\x44\x8B\x14\x25" ADDRESS_TMP_VAR // mov r10, [ADDRESS_TMP_VAR]
                    )

DEF_CMD(POPR_BX,    FST_TMP_VAR ADDRESS_TMP_VAR  // fstp [ADDRESS_TMP_VAR]
                    "\x8B\x1C\x25" ADDRESS_TMP_VAR // mov rbx, [ADDRESS_TMP_VAR]
                    )

DEF_CMD(POPR_CX,    FST_TMP_VAR ADDRESS_TMP_VAR  // fstp [ADDRESS_TMP_VAR]
                    "\x8B\x0C\x25" ADDRESS_TMP_VAR// mov rcx, [ADDRESS_TMP_VAR]
                    )

DEF_CMD(POPR_DX,    FST_TMP_VAR ADDRESS_TMP_VAR  // fstp [ADDRESS_TMP_VAR]
                    "\x8B\x14\x25" ADDRESS_TMP_VAR// mov rdx, [ADDRESS_TMP_VAR]
                    )

DEF_CMD(RET, "\xC3" //ret
                    )

DEF_CMD_JMP(CALL, "\xE8" //call
                    )

DEF_CMD_JMP(JE, BYTE_COM_JMP
                "\x84"
                    )
DEF_CMD_JMP(JNE, BYTE_COM_JMP
                "\x85"
                    )
DEF_CMD_JMP(JA, BYTE_COM_JMP 
                "\x87"
                    )
DEF_CMD_JMP(JAE, BYTE_COM_JMP 
                "\x83"
                    )
DEF_CMD_JMP(JB, BYTE_COM_JMP
                "\x82"
                    )
DEF_CMD_JMP(JBE, BYTE_COM_JMP        
                "\x86" 
                    )




