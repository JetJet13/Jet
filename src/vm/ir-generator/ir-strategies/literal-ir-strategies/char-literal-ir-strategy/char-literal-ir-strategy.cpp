//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/IR/Constants.h>
#include "char-literal-ir-strategy.h"

llvm::Value* CharLiteralIRStrategy::generate(ASTCharLiteralNode* node, std::unique_ptr<llvm::LLVMContext>* context) {
    return llvm::ConstantInt::get(**context, llvm::APInt(CHAR_BIT, node->getValue()));
}