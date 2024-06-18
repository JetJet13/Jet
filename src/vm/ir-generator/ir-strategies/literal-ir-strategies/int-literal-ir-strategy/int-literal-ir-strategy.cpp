//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/ADT/APSInt.h>
#include <llvm/IR/Constants.h>
#include "int-literal-ir-strategy.h"

llvm::Value* IntLiteralIRStrategy::generate(ASTIntLiteralNode* node, std::unique_ptr<llvm::LLVMContext>* context) {
    return llvm::ConstantInt::get(**context, llvm::APSInt(32, node->getValue()));
}