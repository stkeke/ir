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

	ir_ref _op1 = ir_PARAM(IR_DOUBLE, "param1", 1);
	ir_ref _op2 = ir_PARAM(IR_DOUBLE, "param2", 2);

	ir_ref  c  = ir_NEG_C(_op1);
	ir_ref  i8 = ir_NEG_I8(_op1);
	ir_ref  i16 = ir_NEG_I16(_op1);
	ir_ref  i32 = ir_NEG_I32(_op1);
	ir_ref  i64 = ir_NEG_I64(_op1);
	ir_ref  d = ir_NEG_D(_op1);
	ir_ref  f = ir_NEG_F(_op1);

	ir_RETURN(d);
}

#define USE_CUSTOM_RUN
typedef double (*myfunc_t)(double, double);

void run_myfunc(myfunc_t func)
{
    if (func) {
        printf("IR func returned: %f\n", func(10, 5));
    }
}

#include "exmplfrm.h"
