/*
 * IR - Lightweight JIT Compilation Framework
 * (Exmaples package)
 * Copyright (C) 2023 by IR project.
 * Authors: Anatol Belski <anbelski@linux.microsoft.com>
 */

#include "ir.h"
#include "ir_builder.h"
#include <stdlib.h>

void gen_myfunc(ir_ctx *ctx)
{
	ir_START();
	ir_ref divident = ir_PARAM(IR_I32, "divident", 1);
	ir_ref op1 = ir_MOD_I32(divident, ir_CONST_I32(2));
	// ir_ref ret = ir_VAR(IR_BOOL, "ret");
	ir_ref ret = ir_ALLOCA(ir_CONST_ADDR(sizeof(ir_insn)));

	ir_ref if1 = ir_IF(ir_EQ(op1, ir_CONST_I32(0)));
	ir_IF_TRUE(if1);
		// even number
		ir_STORE(ret, IR_TRUE);
		ir_ref end1 = ir_END();
	ir_IF_FALSE(if1);
		ir_STORE(ret, IR_FALSE);
		ir_ref end2 = ir_END();

	ir_MERGE_2(end1, end2);
	ir_ref ret2 = ir_LOAD_B(ret);
	ir_AFREE(ir_CONST_ADDR(sizeof(ir_insn)));
	ir_RETURN(ret2);
}

#define USE_CUSTOM_RUN
typedef bool (*myfunc_t)(int32_t);
void run_myfunc(myfunc_t func)
{
	if (func) {
		printf("%d is even: %d\n", 2,  ((myfunc_t)func)(2));
		printf("%d is even: %d\n", 3,  ((myfunc_t)func)(3));
	}
}

#include "exmplfrm.h"
