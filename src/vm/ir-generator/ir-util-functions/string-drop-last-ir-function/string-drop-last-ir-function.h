//
// Created by Johny Georges on 2026-03-21.
//

#ifndef JETLANG_STRING_DROP_LAST_IR_FUNCTION_H
#define JETLANG_STRING_DROP_LAST_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class StringDropLastIRFunction {
public:
    static std::string getStringDropLastIRFunctionName();
    static void generateStringDropLastFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_STRING_DROP_LAST_IR_FUNCTION_H
