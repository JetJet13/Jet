//
// Created by Johny Georges on 2026-03-21.
//

#ifndef JETLANG_STRING_DROP_IR_FUNCTION_H
#define JETLANG_STRING_DROP_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class StringDropIRFunction {
public:
    static std::string getStringDropIRFunctionName();
    static void generateStringDropFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_STRING_DROP_IR_FUNCTION_H
