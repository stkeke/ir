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
//  int32_t myfunc(int32_t num) {
// 	int remainder = num % 3;
//  switch (remainder)
// 	{
// 	case 0:
// 		num = num * 3;
// 		break;
// 	case 1:
// 		num = num + 1;
// 		break;
// 	case 2:
// 		num = num - 2;
// 		break;
// 	default:
// 		break;
// 	}
//  return num;
// }


// IR function to compile to native code
// Do NOT change function signature
void gen_myfunc(ir_ctx *ctx)
{
	ir_ref divisor = ir_CONST_I32(3);
	ir_ref rem0 = ir_CONST_I32(0);
	ir_ref rem1 = ir_CONST_I32(1);
	ir_ref rem2 = ir_CONST_I32(2);

	ir_START();
	ir_ref num = ir_PARAM(IR_I32, "num", 1);
	ir_ref rets[4], ends[4];
	ir_ref remainder = ir_MOD_I32(num, divisor);

	ir_ref s = ir_SWITCH(remainder);
	ir_CASE_VAL(s, rem0);
		rets[0] = ir_MUL_I32(num, ir_CONST_I32(3));
		ends[0] = ir_END();
	ir_CASE_VAL(s, rem1);
		rets[1] = ir_ADD_I32(num, ir_CONST_I32(1));
		ends[1] = ir_END();
	ir_CASE_VAL(s, rem2);
		rets[2] = ir_SUB_I32(num, ir_CONST_I32(2));
		ends[2] = ir_END();
	ir_CASE_DEFAULT(s);
		rets[3] = rets[2];
		ends[3] = ir_END();

	ir_MERGE_N(4, ends);
	ir_ref ret = ir_PHI_N(4, rets);

	ir_RETURN(ret);
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
		printf("count=%d total=%d\n", 0,  ((myfunc_t)func)(0));
		printf("count=%d total=%d\n", 1,  ((myfunc_t)func)(1));
		printf("count=%d total=%d\n", 2,  ((myfunc_t)func)(2));
	}
}

// Import example framework -
//   standard run_myfunc() and main() functions
#include "exmplfrm.h"
