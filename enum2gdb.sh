#!/usr/bin/bash


function gen_gdb()
{
	local index="$1"
	local myenum="$2"

	echo -e "\tset \$op = \$arg0"
	for e in $myenum
	do
		e=$(echo $e | sed -e 's/,//')
		echo -e "\tif \$op == $e || \$op == $index"
		echo -e "\t\tprintf \"%s(%d)\", \"$e\", \$op"
		echo -e "\tend"

		index=$((index+1))
	done

}

openum="IR_NOP, IR_C_BOOL, IR_C_U8, IR_C_U16, IR_C_U32, IR_C_U64, IR_C_ADDR, IR_C_CHAR, IR_C_I8, IR_C_I16, IR_C_I32, IR_C_I64, IR_C_DOUBLE, IR_C_FLOAT, IR_EQ, IR_NE, IR_LT, IR_GE, IR_LE, IR_GT, IR_ULT, IR_UGE, IR_ULE, IR_UGT, IR_ADD, IR_SUB, IR_MUL, IR_DIV, IR_MOD, IR_NEG, IR_ABS, IR_SEXT, IR_ZEXT, IR_TRUNC, IR_BITCAST, IR_INT2FP, IR_FP2INT, IR_FP2FP, IR_ADD_OV, IR_SUB_OV, IR_MUL_OV, IR_OVERFLOW, IR_NOT, IR_OR, IR_AND, IR_XOR, IR_SHL, IR_SHR, IR_SAR, IR_ROL, IR_ROR, IR_BSWAP, IR_MIN, IR_MAX, IR_COND, IR_PHI, IR_COPY, IR_PI, IR_PARAM, IR_VAR, IR_FUNC_ADDR, IR_FUNC, IR_STR, IR_CALL, IR_TAILCALL, IR_ALLOCA, IR_AFREE, IR_VADDR, IR_VLOAD, IR_VSTORE, IR_RLOAD, IR_RSTORE, IR_LOAD, IR_STORE, IR_TLS, IR_TRAP, IR_GUARD, IR_GUARD_NOT, IR_SNAPSHOT, IR_START, IR_ENTRY, IR_BEGIN, IR_IF_TRUE, IR_IF_FALSE, IR_CASE_VAL, IR_CASE_DEFAULT, IR_MERGE, IR_LOOP_BEGIN, IR_END, IR_LOOP_END, IR_IF, IR_SWITCH, IR_RETURN, IR_IJMP, IR_UNREACHABLE, IR_EXITCALL"

typeenum="IR_VOID, IR_BOOL, IR_U8, IR_U16, IR_U32, IR_U64, IR_ADDR, IR_CHAR, IR_I8, IR_I16, IR_I32, IR_I64, IR_DOUBLE, IR_FLOAT,"

rules="	IR_CMP_INT,
	IR_CMP_FP,
	IR_MUL_INT,
	IR_DIV_INT,
	IR_MOD_INT,
	IR_TEST_INT,
	IR_SETCC_INT,
	IR_TESTCC_INT,
	IR_LEA_OB,
	IR_LEA_SI,
	IR_LEA_SIB,
	IR_LEA_IB,
	IR_LEA_SI_O,
	IR_LEA_SIB_O,
	IR_LEA_IB_O,
	IR_LEA_I_OB,
	IR_LEA_OB_I,
	IR_LEA_OB_SI,
	IR_LEA_SI_OB,
	IR_LEA_B_SI,
	IR_LEA_SI_B,
	IR_INC,
	IR_DEC,
	IR_MUL_PWR2,
	IR_DIV_PWR2,
	IR_MOD_PWR2,
	IR_BOOL_NOT_INT,
	IR_ABS_INT,
	IR_OP_INT,
	IR_OP_FP,
	IR_IMUL3,
	IR_BINOP_INT,
	IR_BINOP_SSE2,
	IR_BINOP_AVX,
	IR_SHIFT,
	IR_SHIFT_CONST,
	IR_COPY_INT,
	IR_COPY_FP,
	IR_CMP_AND_BRANCH_INT,
	IR_CMP_AND_BRANCH_FP,
	IR_TEST_AND_BRANCH_INT,
	IR_JCC_INT,
	IR_GUARD_CMP_INT,
	IR_GUARD_CMP_FP,
	IR_GUARD_TEST_INT,
	IR_GUARD_JCC_INT,
	IR_GUARD_OVERFLOW,
	IR_OVERFLOW_AND_BRANCH,
	IR_MIN_MAX_INT,
	IR_MEM_OP_INT,
	IR_MEM_INC,
	IR_MEM_DEC,
	IR_MEM_MUL_PWR2,
	IR_MEM_DIV_PWR2,
	IR_MEM_MOD_PWR2,
	IR_MEM_BINOP_INT,
	IR_MEM_SHIFT,
	IR_MEM_SHIFT_CONST,
	IR_REG_BINOP_INT,
	IR_VSTORE_INT,
	IR_VSTORE_FP,
	IR_LOAD_INT,
	IR_LOAD_FP,
	IR_STORE_INT,
	IR_STORE_FP,
	IR_IF_INT,
	IR_RETURN_VOID,
	IR_RETURN_INT,
	IR_RETURN_FP,"
### op enum
echo "define print_op"
gen_gdb 0 "$openum"
echo "end"
echo

### type enum
echo "define print_type"
gen_gdb 0 "$typeenum"
echo "end"
echo

### rules enum
echo "define print_rule"
gen_gdb 96 "$rules"
echo "end"
echo
