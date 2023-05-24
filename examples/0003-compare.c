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

	ir_ref _op1 = ir_PARAM(IR_I32, "param1", 1);
	ir_ref _op2 = ir_PARAM(IR_I32, "param2", 2);

	ir_ref eq = ir_EQ(_op1, _op2);
	ir_ref ne = ir_NE(_op1, _op2);
	ir_ref lt = ir_LT(_op1, _op2);
	ir_ref ge = ir_GE(_op1, _op2);
	ir_ref le = ir_LE(_op1, _op2);
	ir_ref gt = ir_GT(_op1, _op2);

	ir_ref ult = ir_ULT(_op1, _op2);
	ir_ref uge = ir_UGE(_op1, _op2);
	ir_ref ule = ir_ULE(_op1, _op2);
	ir_ref ugt = ir_UGT(_op1, _op2);

	ir_RETURN(ugt);
}

#define USE_CUSTOM_RUN
typedef bool (*myfunc_t)(uint32_t, uint32_t);

void run_myfunc(myfunc_t func)
{
    if (func) {
        printf("IR func returned: %d\n", func(10, 5));
    }
}

#include "exmplfrm.h"
