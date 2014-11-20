#include <llvm-c/Core.h>

int main(int argc, char **argv)
{
    LLVMModuleRef module = LLVMModuleCreateWithName("sample");

    LLVMDisposeModule(module);

    return 0;
}
