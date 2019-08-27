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
    // if(detail != NULL)
    //     fprintf(detail, "\n %d", in.opcode);
switch (in.opcode){
case ESPECIAL:
    switch (in.s_instrucao.func){
        case TADD:
            if(detail != NULL){
                fprintf(detail, "\t\tadd ");
                reg(in.s_instrucao.rd);
                reg(in.s_instrucao.rs);
                reg(in.s_instrucao.rt);
                fprintf(detail, "\n");
            }
            break;
        case TAND:
            if(detail != NULL){
                fprintf(detail, "\t\tand ");
                reg(in.s_instrucao.rd);
                reg(in.s_instrucao.rs);
                reg(in.s_instrucao.rt);
                fprintf(detail, "\n");
            }
            break;
        case TDIV:
            if(detail != NULL){
                fprintf(detail, "\t\tdiv ");
                reg(in.s_instrucao.rs);
                reg(in.s_instrucao.rt);
                fprintf(detail, "\n");
            }
            break;
        case TJR:
            if(detail != NULL){
                fprintf(detail, "\t\tjr ");
                reg(in.s_instrucao.rs);
                fprintf(detail, "\n");
            }
            break;
        case TMFHI:
            if(detail != NULL){
                fprintf(detail, "\t\tmghi ");
                reg(in.s_instrucao.rd);
                fprintf(detail, "\n");
            }
            break;
        case TMFLO:
            if(detail != NULL){
                fprintf(detail, "\t\tmflo ");
                reg(in.s_instrucao.rd);
                fprintf(detail, "\n");
            }
            break;
        case TMOVN:
            if(detail != NULL){
                fprintf(detail, "\t\tmovn ");
                reg(in.s_instrucao.rd);
                reg(in.s_instrucao.rs);
                reg(in.s_instrucao.rt);
                fprintf(detail, "\n");
            }
            break;
        case TMOVZ:
            if(detail != NULL){
                fprintf(detail, "\t\tmovz ");
                reg(in.s_instrucao.rd);
                reg(in.s_instrucao.rs);
                reg(in.s_instrucao.rt);
                fprintf(detail, "\n");
            }
            break;
        case TMTHI:
            if(detail != NULL){
                fprintf(detail, "\t\tmthi ");
                reg(in.s_instrucao.rs);
                fprintf(detail, "\n");
            }
            break;
        case TMTLO:
            if(detail != NULL){
                fprintf(detail, "\t\tmtlo ");
                reg(in.s_instrucao.rs);
                fprintf(detail, "\n");
            }
            break;
        case TMULT:
            if(detail != NULL){
                fprintf(detail, "\t\tmult ");
                reg(in.s_instrucao.rs);
                reg(in.s_instrucao.rt);
                fprintf(detail, "\n");
            }
            break;
        case TNOP:
            if(detail != NULL)
                fprintf(detail, "\t\tnop \n");
            break;
        case TNOR:
            if(detail != NULL){
                fprintf(detail, "\t\tnor ");
                reg(in.s_instrucao.rd);
                reg(in.s_instrucao.rs);
                reg(in.s_instrucao.rt);
                fprintf(detail, "\n");
            }
            break;
        case TOR:
            if(detail != NULL){
                fprintf(detail, "\t\tor ");
                reg(in.s_instrucao.rd);
                reg(in.s_instrucao.rs);
                reg(in.s_instrucao.rt);
                fprintf(detail, "\n");
            }
            break;
        case TSUB:
            if(detail != NULL){
                fprintf(detail, "\t\tsub ");
                reg(in.s_instrucao.rd);
                reg(in.s_instrucao.rs);
                reg(in.s_instrucao.rt);
                fprintf(detail, "\n");
            }
            break;
        case TXOR:
            if(detail != NULL){
                fprintf(detail, "\t\txor ");
                reg(in.s_instrucao.rd);
                reg(in.s_instrucao.rs);
                reg(in.s_instrucao.rt);
                fprintf(detail, "\n");
            }
            break;
        }   
break;
case ESPECIAL2:
    switch (in.s2_instrucao.func){
    case TMSUB:
        if(detail != NULL){
            fprintf(detail, "\t\tmsub ");
            reg(in.s2_instrucao.rs);
            reg(in.s2_instrucao.rt);
            fprintf(detail, "\n");
        }
        break;
    case TMUL:
        if(detail != NULL){
            fprintf(detail, "\t\tmul ");
            reg(in.s2_instrucao.rd);
            reg(in.s2_instrucao.rs);
            reg(in.s2_instrucao.rt);
            fprintf(detail, "\n");
        }
        break;
    case TMADD:
        if(detail != NULL){
            fprintf(detail, "\t\tmadd ");
            reg(in.s2_instrucao.rs);
            reg(in.s2_instrucao.rt);
            fprintf(detail, "\n");
        }
        break;
    default:
        break;
    }
break;
case REGIMM:
    switch (in.r_instrucao.id){
    case TBGEZ:
        if(detail != NULL){
            fprintf(detail, "\t\tbgez ");
            reg(in.r_instrucao.rs);
            reg(in.r_instrucao.offset);
            fprintf(detail, "\n");
        }
        break;
    case TBLTZ:
        if(detail != NULL){
            fprintf(detail, "\t\tbltz ");
            reg(in.r_instrucao.rs);
            reg(in.r_instrucao.offset);
            fprintf(detail, "\n");
        }
        break;
    default:
        break;
    }
break;
case TJ:
    if(detail != NULL){
        fprintf(detail, "\t\tj ");
        fprintf(detail, "%d\n", in.j_instrucao.addr);
    }
    break;
case TADDI:
    if(detail != NULL){
        fprintf(detail, "\t\taddi");
        reg(in.i_instrucao.rt);
        reg(in.i_instrucao.rs);
        fprintf(detail, " %d ", in.i_instrucao.imediato);
        fprintf(detail, "\n");
    }
    break;
case TANDI:
    if(detail != NULL){
        fprintf(detail, "\t\tandi ");
        reg(in.i_instrucao.rt);
        reg(in.i_instrucao.rs);
        fprintf(detail, " %d ", in.i_instrucao.imediato);
        fprintf(detail, "\n");
    }
    break;
// case TB:
//     if(detail != NULL){
//         fprintf(detail, "\t\tb ");
//         fprintf(detail, " %d ", in.i_instrucao.imediato);
//         fprintf(detail, "\n");
//     }
//     break;
    
case TBEQ://ou TB
    if(in.i_instrucao.rs == 0 && in.i_instrucao.rt == 0){
        if(detail != NULL){
            fprintf(detail, "\t\tb ");
            fprintf(detail, " %d ", in.i_instrucao.imediato);
            fprintf(detail, "\n");
        }
    }
    else{
        if(detail != NULL){
            fprintf(detail, "\t\tbeq ");
            reg(in.i_instrucao.rs);
            reg(in.i_instrucao.rt);
            fprintf(detail, " %d ", in.i_instrucao.imediato);
            fprintf(detail, "\n");
        }
    }
    break;
case TBEQL:
    if(detail != NULL){
        fprintf(detail, "\t\tbeql ");
        reg(in.i_instrucao.rs);
        reg(in.i_instrucao.rt);
        fprintf(detail, " %d ", in.i_instrucao.imediato);
        fprintf(detail, "\n");
    }
    break;
case TBGTZ:
    if(detail != NULL){
        fprintf(detail, "\t\tbgtz ");
        reg(in.i_instrucao.rs);
        fprintf(detail, " %d ", in.i_instrucao.imediato);
        fprintf(detail, "\n");
    }
    break;
case TBLEZ:
    if(detail != NULL){
        fprintf(detail, "\t\tblez ");
        reg(in.i_instrucao.rs);
        fprintf(detail, " %d ", in.i_instrucao.imediato);
        fprintf(detail, "\n");
    }
    break;
case TBNE:
    if(detail != NULL){
        fprintf(detail, "\t\tbne ");
        reg(in.i_instrucao.rs);
        reg(in.i_instrucao.rt);
        fprintf(detail, " %d ", in.i_instrucao.imediato);
        fprintf(detail, "\n");
    }
    break;
case TLUI:
    if(detail != NULL){
        fprintf(detail, "\t\tlui ");
        reg(in.i_instrucao.rt);
        fprintf(detail, " %d ", in.i_instrucao.imediato);
        fprintf(detail, "\n");
    }
    break;
case TORI:
    if(detail != NULL){
        fprintf(detail, "\t\tori ");
        reg(in.i_instrucao.rt);
        reg(in.i_instrucao.rs);
        fprintf(detail, " %d ", in.i_instrucao.imediato);
        fprintf(detail, "\n");
    }
    break;
case TXORI:
    if(detail != NULL){
        fprintf(detail, "\t\txori ");
        reg(in.i_instrucao.rt);
        reg(in.i_instrucao.rs);
        fprintf(detail, " %d ", in.i_instrucao.imediato);
        fprintf(detail, "\n");
    }
    break;
    default:
        break;
    }

}
