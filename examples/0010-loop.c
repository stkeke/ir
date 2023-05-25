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
 *
 *     total *= 2;
 *     return total;
 * }
 */

// IR function to compile to native code
// Do NOT change function signature
void gen_myfunc(ir_ctx *ctx)
{
	ir_ref init_idx = ir_CONST_I32(1);
	ir_ref init_total = ir_CONST_I32(0);

	ir_START();
	ir_ref cnt = ir_PARAM(IR_I32, "loop_count", 1);

	/* loop begin */
	ir_ref loop = ir_LOOP_BEGIN(ir_END());

	ir_ref phi_idx = ir_PHI_2(init_idx, IR_UNUSED);
	ir_ref phi_total = ir_PHI_2(init_total, IR_UNUSED);

	ir_ref ret = ir_ADD_I32(phi_total, phi_idx);
	ir_ref phi_idx_2 = ir_ADD_I32(phi_idx, ir_CONST_I32(1));

	ir_ref cond = ir_GE(phi_idx, cnt);
	ir_ref if1 = ir_IF(cond);
	ir_IF_TRUE(if1);
		// ir_RETURN(ret);
		ir_ref end = ir_END();
	ir_IF_FALSE(if1); /* loop exit */
		ir_ref loop_end = ir_LOOP_END(); /* loop end */
	ir_MERGE_SET_OP(loop, 2, loop_end);
	ir_PHI_SET_OP(phi_idx, 2, phi_idx_2);
	ir_PHI_SET_OP(phi_total, 2, ret);

	ir_BEGIN(end);
	ir_ref ret2 = ir_ADD_I32(ret, ret);
	ir_RETURN(ret2);
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
		printf("count=%d total=%d\n", 1,  ((myfunc_t)func)(1));
		printf("count=%d total=%d\n", 5,  ((myfunc_t)func)(5));
		printf("count=%d total=%d\n", 10,  ((myfunc_t)func)(10));
	}
}

// Import example framework -
//   standard run_myfunc() and main() functions
#include "exmplfrm.h"
