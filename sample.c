#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/Target.h>
#include <llvm-c/ExecutionEngine.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

int main(int argc, char **argv)
{
    LLVMModuleRef module = LLVMModuleCreateWithName("sample");
    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMExecutionEngineRef exec_engine;

    LLVMInitializeNativeTarget();
	LLVMLinkInJIT();

    char *err;
    if (LLVMCreateExecutionEngineForModule(&exec_engine, module, &err)) {
		fprintf(stderr, "error: %s\n", err);
		LLVMDisposeMessage(err);
		return -1;
	}

    LLVMTypeRef *arg_types = malloc(2 * sizeof(LLVMTypeRef));
    arg_types[0] = LLVMInt8Type();
    arg_types[1] = LLVMInt8Type();
    LLVMValueRef fn = LLVMAddFunction(module, "add", LLVMFunctionType(LLVMInt8Type(), arg_types, 2, 0));

    LLVMValueRef *arg_values = malloc(2 * sizeof(LLVMValueRef));
    LLVMGetParams(fn, arg_values);
    LLVMSetValueName(arg_values[0], "x");
    LLVMSetValueName(arg_values[1], "y");

    LLVMBasicBlockRef basic_block = LLVMAppendBasicBlock(fn, "entry");

    LLVMPositionBuilderAtEnd(builder, basic_block);
    LLVMValueRef res = LLVMBuildAdd(builder, arg_values[0], arg_values[1], "res");
    LLVMBuildRet(builder, res);

    LLVMVerifyFunction(fn, LLVMPrintMessageAction);

    LLVMPassManagerRef pass_mgr = LLVMCreateFunctionPassManagerForModule(module);
    LLVMAddTargetData(LLVMGetExecutionEngineTargetData(exec_engine), pass_mgr);
    LLVMRunFunctionPassManager(pass_mgr, fn);

    typedef int8_t (*toplvl_fp_t)(int8_t, int8_t);
    toplvl_fp_t fp;
    fp = LLVMGetPointerToGlobal(exec_engine, fn);
    fprintf(stderr, "Result: %hhd\n\n", fp(1, 2));

    LLVMDumpModule(module);

    LLVMDisposePassManager(pass_mgr);
    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
    free(arg_types);
    free(arg_values);

    return 0;
}
