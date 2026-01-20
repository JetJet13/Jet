//
// Created by Johny Georges on 2025-10-25.
//

#ifndef JETLANG_SREF_WITH_IR_FUNCTION_H
#define JETLANG_SREF_WITH_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class SrefWithIRFunction {
public:
    static std::string getSrefWithIRFunctionName();
    static void generateSrefWithFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_SREF_WITH_IR_FUNCTION_H
