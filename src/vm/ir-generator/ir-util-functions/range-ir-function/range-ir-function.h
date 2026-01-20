//
// Created by Johny Georges on 2025-05-27.
//

#ifndef JETLANG_RANGE_IR_FUNCTION_H
#define JETLANG_RANGE_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class RangeIRFunction {
public:
    static std::string getRange1pIRFunctionName();
    static std::string getRange2pIRFunctionName();
    static std::string getRange3pIRFunctionName();
    static void generateRange1pFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateRange2pFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateRange3pFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_RANGE_IR_FUNCTION_H
