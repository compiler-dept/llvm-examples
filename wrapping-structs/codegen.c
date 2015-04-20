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

  // Erstelle LLVM Struct Typen fuer unser event
  LLVMTypeRef wrapper = LLVMStructCreateNamed(LLVMGetModuleContext(module), "position_event");
  // Erstelle Felder fuer struct
  LLVMTypeRef element_types[] = {
    LLVMInt16Type(),
    LLVMInt16Type(),
    LLVMInt16Type()
  };
  // Fuege felder dem struct hinzu
  LLVMStructSetBody(wrapper, element_types, 3, 0);

  // Erstelle die paramerliste fuer die funktion. Sie enthaelt typ "pointer auf unser struct"
  LLVMTypeRef args[] = { LLVMPointerType(wrapper, 0) };
  // Erstelle die funktion, fuege ihr die parameterliste hinzu, rueckgabetyp ist void
  LLVMValueRef fn = LLVMAddFunction(module, "add", LLVMFunctionType(LLVMVoidType(), args, 1, 0));

  // Erzeuge variable fuer den parameter
  LLVMValueRef arg_value;
  // hole den parameter
  LLVMGetParams(fn, &arg_value);
  // benenne den parameter
  LLVMSetValueName(arg_value, "ev");

  // erzeuge funktionsrumpf
  LLVMBasicBlockRef basic_block = LLVMAppendBasicBlock(fn, "param");
  // erzeuge builder
  LLVMBuilderRef builder = LLVMCreateBuilder();
  LLVMPositionBuilderAtEnd(builder, basic_block);

  // hole pointer auf 1 feld
  LLVMValueRef _x = LLVMBuildStructGEP(builder, arg_value, 0, "_x");
  // hole pointer auf 2 feld
  LLVMValueRef _y = LLVMBuildStructGEP(builder, arg_value, 1, "_y");
  // hole pointer auf 3 feld
  LLVMValueRef _z = LLVMBuildStructGEP(builder, arg_value, 2, "_z");

  // speichere werte der beiden felder in variablen x und y
  LLVMValueRef x = LLVMBuildLoad(builder, _x, "x");
  LLVMValueRef y = LLVMBuildLoad(builder, _y, "y");

  // addiere werte und speichere ergebnis in res
  LLVMValueRef res = LLVMBuildAdd(builder, x, y, "res");
  // schreibe res in drittes feld
  LLVMBuildStore(builder, res, _z);

  // return void
  LLVMBuildRetVoid(builder);

  LLVMVerifyFunction(fn, LLVMPrintMessageAction);


  LLVMDumpModule(module);
  LLVMWriteBitcodeToFile(module, "wrap.bc");

  LLVMDisposeBuilder(builder);
  LLVMDisposeModule(module);


  return 0;
}
