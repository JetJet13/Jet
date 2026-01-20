//
// Created by Johny Georges on 2024-09-26.
//

#ifndef JETLANG_COPY_STRING_IR_FUNCTION_H
#define JETLANG_COPY_STRING_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class CopyStringIRFunction {
public:
    static std::string getCopyStringIRFunctionName();
    static void generateCopyStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_COPY_STRING_IR_FUNCTION_H
