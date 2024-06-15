//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/ADT/APFloat.h>
#include "float-literal-ir-strategy.h"

llvm::Value* FloatLiteralIRStrategy::generate(ASTFloatLiteralNode* node, std::unique_ptr<llvm::LLVMContext>* context) {
    return llvm::ConstantFP::get(**context, llvm::APFloat(node->getValue()));
}