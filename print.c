#include "print.h"

void reg(int r){
    switch (r){
    case 0:
        if(detail != NULL)
            fprintf(detail, " z0 ");
        break;
    case 1:
        if(detail != NULL)
            fprintf(detail, " $at ");
        break;
    case 2:
        if(detail != NULL)
            fprintf(detail, " $v0 ");
        break;
    case 3:
        if(detail != NULL)
            fprintf(detail, " $v1 ");
        break;
    case 4:
        if(detail != NULL)
            fprintf(detail, " $a0 ");
        break;
    case 5:
        if(detail != NULL)
            fprintf(detail, " $a1 ");
        break;
    case 6:
        if(detail != NULL)
            fprintf(detail, " $a2 ");
        break;
    case 7:
        if(detail != NULL)
            fprintf(detail, " $a3 ");
        break;
    case 8:
        if(detail != NULL)
            fprintf(detail, " $t0 ");
        break;
    case 9:
        if(detail != NULL)
            fprintf(detail, " $t1 ");
        break;
    case 10:
        if(detail != NULL)
            fprintf(detail, " $t2 ");
        break;
    case 11:
        if(detail != NULL)
            fprintf(detail, " $t3 ");
        break;
    case 12:
        if(detail != NULL)
            fprintf(detail, " $t4 ");
        break;
    case 13:
        if(detail != NULL)
            fprintf(detail, " $t5 ");
        break;
    case 14:
        if(detail != NULL)
            fprintf(detail, " $t6 ");
        break;
    case 15:
        if(detail != NULL)
            fprintf(detail, " $t7 ");
        break;
    case 16:
        if(detail != NULL)
            fprintf(detail, " $s0 ");
        break;
    case 17:
        if(detail != NULL)
            fprintf(detail, " $s1 ");
        break;
    case 18:
        if(detail != NULL)
            fprintf(detail, " $s2 ");
        break;
    case 19:
        if(detail != NULL)
            fprintf(detail, " $s3 ");
        break;
    case 20:
        if(detail != NULL)
            fprintf(detail, " $s4 ");
        break;
    case 21:
        if(detail != NULL)
            fprintf(detail, " $s5 ");
        break;
    case 22:
        if(detail != NULL)
            fprintf(detail, " $s6 ");
        break;
    case 23:
        if(detail != NULL)
            fprintf(detail, " $s7 ");
        break;
    case 24:
        if(detail != NULL)
            fprintf(detail, " $t8 ");
        break;
    case 25:
        if(detail != NULL)
            fprintf(detail, " $t9 ");
        break;
    case 26:
        if(detail != NULL)
            fprintf(detail, " $k0 ");
        break;
    case 27:
        if(detail != NULL)
            fprintf(detail, " $k1 ");
        break;
    case 28:
        if(detail != NULL)
            fprintf(detail, " $gp ");
        break;
    case 29:
        if(detail != NULL)
            fprintf(detail, " $sp ");
        break;
    case 30:
        if(detail != NULL)
            fprintf(detail, " $fp/s8 ");
        break;
    }
    
}

void printar(Inst in){
   // printf("\n %d", in.opcode);
 if(detail != NULL)
    fprintf(detail, "\n %d", in.opcode);
    //fprintf(detail, "\n %d", in.opcode);
switch (in.opcode){
case ESPECIAL:
    // in.opcode = instrucao >> 26 & MASCARA;
	// 	in.s_instrucao.rs = instrucao >> 21 & MASCARA;
	// 	in.s_instrucao.rt = instrucao >> 16 & MASCARA;
	// 	in.s_instrucao.rd = instrucao >> 11 & MASCARA;
	// 	in.s_instrucao.shamt = instrucao >> 6 & MASCARA;
	// 	in.s_instrucao.func = instrucao & 63;
    switch (in.s_instrucao.func){
        case TADD:
            if(detail != NULL){
                fprintf(detail, "\t\tadd ");
            }
            break;
        case TAND:
            if(detail != NULL)
                fprintf(detail, "\t\tand ");
            break;
        case TDIV:
            if(detail != NULL)
                fprintf(detail, "\t\tdiv ");
            break;
        case TJR:
            if(detail != NULL)
                fprintf(detail, "\t\tjr ");
            break;
        case TMFHI:
            if(detail != NULL)
                fprintf(detail, "\t\tmghi ");
            break;
        case TMFLO:
            if(detail != NULL)
                fprintf(detail, "\t\tmflo ");
            break;
        case TMOVN:
            if(detail != NULL)
                fprintf(detail, "\t\tmovn ");
            break;
        case TMOVZ:
            if(detail != NULL)
                fprintf(detail, "\t\tmovz ");
            break;
        case TMTHI:
            if(detail != NULL)
                fprintf(detail, "\t\tmthi ");
            break;
        case TMTLO:
            if(detail != NULL)
                fprintf(detail, "\t\tmtlo ");
            break;
        case TMULT:
            if(detail != NULL)
                fprintf(detail, "\t\tmult ");
            break;
        case TNOP:
            if(detail != NULL)
                fprintf(detail, "\t\tnop ");
            break;
        case TNOR:
            if(detail != NULL)
                fprintf(detail, "\t\tnor ");
            break;
        case TOR:
            if(detail != NULL)
                fprintf(detail, "\t\tor ");
            break;
        case TSUB:
            if(detail != NULL)
                fprintf(detail, "\t\tsub ");
            break;
        case TXOR:
            if(detail != NULL)
                fprintf(detail, "\t\txor ");
            break;
        }   
case ESPECIAL2:
    switch (in.s2_instrucao.func){
    case TMSUB:
        if(detail != NULL)
            fprintf(detail, "\t\tmsub ");
        break;
    case TMUL:
        if(detail != NULL)
            fprintf(detail, "\t\tmul ");
        break;
    default: 
        if(detail != NULL)
             fprintf(detail, "\t\tmadd ");
        break;
    }
case REGIMM:
    switch (in.r_instrucao.id){
    case TBGEZ:
        if(detail != NULL)
            fprintf(detail, "\t\tbgez ");
        break;
    case TBLTZ:
        if(detail != NULL)
            fprintf(detail, "\t\tbltz ");
        break;
    }
case SALTO:
    if(detail != NULL)
        fprintf(detail, "\t\tj ");
    break;
case TADDI:
    if(detail != NULL){
        fprintf(detail, "\t\taddi");
        reg(in.i_instrucao.rt);
        reg(in.i_instrucao.rs);
        fprintf(detail, " %d ", in.i_instrucao.imediato);
    }
    break;
case TANDI:
    if(detail != NULL){
        fprintf(detail, "\t\tandi ");
        reg(in.i_instrucao.rt);
        reg(in.i_instrucao.rs);
        fprintf(detail, " %d ", in.i_instrucao.imediato);
    }
    break;
case TB:
    if(detail != NULL)
        fprintf(detail, "\t\tb ");
        fprintf(detail, " %d ", in.i_instrucao.imediato);
    break;
    
    // case TBEQ:
    //     if(detail != NULL)
    //         fprintf(detail, "beq");
    //     break;
case TBEQL:
    if(detail != NULL)
        fprintf(detail, "\t\tbeql ");
    break;
case TBGTZ:
    if(detail != NULL)
        fprintf(detail, "\t\tj ");
    break;
case TBLEZ:
    if(detail != NULL)
        fprintf(detail, "\t\tblez ");
    break;
case TBNE:
    if(detail != NULL)
        fprintf(detail, "\t\tbne ");
    break;
case TLUI:
    if(detail != NULL)
        fprintf(detail, "\t\tlui ");
    break;
case TORI:
    if(detail != NULL)
        fprintf(detail, "\t\tori ");
    break;
case TXORI:
    if(detail != NULL)
        fprintf(detail, "\t\txori ");
    break;
    }
}

