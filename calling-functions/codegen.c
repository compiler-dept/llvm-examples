#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/Target.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/BitWriter.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

int main(int argc, char **argv)
{
  // Erstelle Modul
  LLVMModuleRef module = LLVMModuleCreateWithName("sample");


  LLVMTypeRef args[] = {LLVMPointerType(LLVMInt8Type(), 0)};
  // Deklariere die externe Funktion
  LLVMValueRef output_func = LLVMAddFunction(module, "output", LLVMFunctionType(LLVMVoidType(), args, 1, 0));

  // Erstelle die funktion, fuege ihr die parameterliste hinzu, rueckgabetyp ist void
  LLVMValueRef main_func = LLVMAddFunction(module, "main", LLVMFunctionType(LLVMVoidType(), NULL, 0, 0));

  // erzeuge funktionsrumpf
  LLVMBasicBlockRef basic_block = LLVMAppendBasicBlock(main_func, "entry");
  // erzeuge builder
  LLVMBuilderRef builder = LLVMCreateBuilder();
  LLVMPositionBuilderAtEnd(builder, basic_block);

  LLVMValueRef string_ptr = LLVMBuildGlobalStringPtr(builder, "Hallo Welt!", "str");
  LLVMBuildCall(builder, output_func, &string_ptr, 1, "");



  // return void
  LLVMBuildRetVoid(builder);

  LLVMVerifyFunction(main_func, LLVMPrintMessageAction);


  LLVMDumpModule(module);
  LLVMWriteBitcodeToFile(module, "main.bc");

  LLVMDisposeBuilder(builder);
  LLVMDisposeModule(module);


  return 0;
}
