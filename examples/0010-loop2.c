/*
 * IR - Lightweight JIT Compilation Framework
 * (Exmaples package)
 * Copyright (C) 2023 by IR project.
 * Authors: Tony Su <tao.su@intel.com>
 */

#include "ir.h"
#include "ir_builder.h"
#include <stdlib.h>

/* Doc: Equivalent C code here */
/*
 * int32_t myfunc(int32_t loop_count) {
 *     int32_t total = 0;
 *     for (int i = 0; i < loop_count; i++) {
 *           total += i;
 *     }
 *     total *= 2;
 *     return total;
 * }
 */

// IR function to compile to native code
// Do NOT change function signature
void gen_myfunc(ir_ctx *ctx)
{
	ir_START();
	ir_ref cnt = ir_PARAM(IR_I32, "loop_count", 1);

	ir_ref total = ir_VAR(IR_I32, "total");
	ir_ref idx  = ir_VAR(IR_I32, "index");

	ir_VSTORE(total, ir_CONST_I32(0));
	ir_VSTORE(idx, ir_CONST_I32(1));

	ir_ref loop = ir_LOOP_BEGIN(ir_END());

	ir_ref if1 = ir_IF(ir_LE(ir_VLOAD_I32(idx), cnt));
	ir_IF_TRUE(if1);
		ir_VSTORE(total, ir_ADD_I32(ir_VLOAD_I32(total), ir_VLOAD_I32(idx)));
		ir_VSTORE(idx, ir_ADD_I32(ir_VLOAD_I32(idx), ir_CONST_I32(1)));

		ir_ref loop_end = ir_LOOP_END();
		ir_MERGE_SET_OP(loop, 2, loop_end);
	ir_IF_FALSE(if1); /* loop exit*/
		// ir_VSTORE(total, ir_MUL_I32(ir_VLOAD_I32(total), ir_CONST_I32(2)));
		ir_RETURN(ir_VLOAD_I32(total));
}

/* Usage: custom and standard run_myfunc()
 *   If your IR function above supports parameters, e.g.
 *       int32_t myfunc(int32_t, int32_t);
 *   a customary run_myfunc() (see template below) should be implemented in
 *   order to pass in your own parameters and run the function.
 *
 *   Otherwise, your IR function is assumed to be parameter-less and
 *   return a value of uint32_t, just like
 *      uint32_t myfunc(void)
 *   In this case, simply remove the run_myfunc() template below and
 *   by default use standard run_myfunc() function provided by 'exmplfrm.h'.
 */
// #define USE_STANDARD_RUN
#define USE_CUSTOM_RUN
typedef int32_t (*myfunc_t)(int32_t);
void run_myfunc(myfunc_t func)
{
	if (func) {
		printf("count=%d total=%d\n", 10,  ((myfunc_t)func)(10));
	}
}

// Import example framework -
//   standard run_myfunc() and main() functions
#include "exmplfrm.h"
