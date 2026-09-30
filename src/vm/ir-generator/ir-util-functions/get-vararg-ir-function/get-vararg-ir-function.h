//
// Created by Johny Georges on 2026-09-29.
//

#ifndef JETLANG_GET_VARARG_IR_FUNCTION_H
#define JETLANG_GET_VARARG_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class GetVarArgIRFunction {
public:
    static std::string getGetVarArgIRFunctionName();
    static void generateGetVarArgFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_GET_VARARG_IR_FUNCTION_H
