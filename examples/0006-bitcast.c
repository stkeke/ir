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
	ir_ref _op2 = ir_PARAM(IR_I32, "param2", 2);

    // ir_ref u8 = ir_BITCAST_U8(_op1);
    // ir_ref u16 = ir_BITCAST_U16(_op1);
    // ir_ref u32 = ir_BITCAST_U32(_op1);
    // ir_ref u64 = ir_BITCAST_U64(_op1);

    // ir_ref addr = ir_BITCAST_A(_op1);
    // ir_ref c = ir_BITCAST_C(_op1);

    // ir_ref i8 = ir_BITCAST_I8(_op1);
    // ir_ref i16 = ir_BITCAST_I16(_op1);
    ir_ref i32 = ir_BITCAST_I32(_op1);
    // ir_ref i64 = ir_BITCAST_I64(_op1);
    // ir_ref d = ir_BITCAST_D(_op1);
    // ir_ref f = ir_BITCAST_F(_op1);

	ir_RETURN(i32);
}

#define USE_CUSTOM_RUN
typedef uint64_t (*myfunc_t)(double, uint32_t);

void run_myfunc(myfunc_t func)
{
    if (func) {
        printf("IR func returned: %f\n", func(-10, 5));
    }
}

#include "exmplfrm.h"
