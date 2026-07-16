//
// Created by Johny Georges on 2025-10-30.
//

#ifndef JETLANG_SHARES_WITH_IR_FUNCTION_H
#define JETLANG_SHARES_WITH_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class SharesWithIRFunction {
public:
    static std::string getSharesWithIRFunctionName();
    static void generateSharesWithFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_SHARES_WITH_IR_FUNCTION_H
