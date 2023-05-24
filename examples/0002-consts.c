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
	ir_ref b      = ir_CONST_BOOL(10);
	ir_ref res8   = ir_CONST_U8(10);
	ir_ref res16  = ir_CONST_U16(10);
	ir_ref res32  = ir_CONST_U32(10);
	ir_ref res64  = ir_CONST_U64(10);
	ir_ref addr   = ir_CONST_ADDR(10);
	ir_ref ch     = ir_CONST_CHAR(10);
	ir_ref resi8  = ir_CONST_I8(10);
	ir_ref resi16 = ir_CONST_I16(10);
	ir_ref resi32 = ir_CONST_I32(10);
	ir_ref resi64 = ir_CONST_I64(10);
	ir_ref d = ir_CONST_DOUBLE(10.0);
	ir_ref f = ir_CONST_FLOAT(10.0);
	ir_RETURN(res32);
}

#include "exmplfrm.h"
