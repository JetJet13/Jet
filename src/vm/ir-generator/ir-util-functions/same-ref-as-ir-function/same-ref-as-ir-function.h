//
// Created by Johny Georges on 2025-10-30.
//

#ifndef JETLANG_SAME_REF_AS_IR_FUNCTION_H
#define JETLANG_SAME_REF_AS_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class SameRefAsIRFunction {
public:
    static std::string getSameRefAsIRFunctionName();
    static void generateSameRefAsFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_SAME_REF_AS_IR_FUNCTION_H
