//
// Created by Johny Georges on 2025-12-12.
//

#ifndef JETLANG_GET_REF_COUNT_IR_FUNCTION_H
#define JETLANG_GET_REF_COUNT_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class GetRefCountIRFunction {
public:
    static std::string getGetRefCountIRFunctionName();
    static void generateGetRefCountFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_GET_REF_COUNT_IR_FUNCTION_H
