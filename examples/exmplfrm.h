/*
 * IR - Lightweight JIT Compilation Framework
 * (Exmaples package)
 * Copyright (C) 2023 by IR project.
 * Authors: Anatol Belski <anbelski@linux.microsoft.com>
 *          Tony Su <tao.su@intel.com>
 */

#ifndef USE_CUSTOM_RUN
typedef uint32_t (*myfunc_t)(void);

/* Standard run() function - run IR function without parameters  */
void run_myfunc(myfunc_t func)
{
    if (func) {
        printf("IR func returned: %d\n", func());
    }
}
#endif /* USE_CUSTOM_RUN */

/* Pointing to standard or customary run_myfunc() function. */
void (*p_func)(myfunc_t) = run_myfunc;

int main(int argc, char **argv)
{
	ir_ctx ctx = {0};

	ir_consistency_check();

	ir_init(&ctx, IR_FUNCTION | IR_OPT_FOLDING, 256, 1024);

	gen_myfunc(&ctx);
	puts("Before Optimization ...");
	ir_save(&ctx, stderr);

	char dot_file[100];
	sprintf(dot_file, "%s.dot", argv[0]);
	FILE* f = fopen(dot_file, "w+");
	ir_dump_dot(&ctx, f);
	fclose(f);

	char dot_cmd[256];
	sprintf(dot_cmd, "./dot.sh %s", dot_file);
	system(dot_cmd);

	size_t size;
	void *entry = ir_jit_compile(&ctx, 2, &size);

	puts("After Optimization ...");
	ir_save(&ctx, stderr);

	if (entry) {
		printf("entry=%p size=%ld\n", entry, size);
		p_func(entry);
	} else {
		printf("ERROR: entry is NULL\n");
	}

	ir_free(&ctx);

	return 0;
}

