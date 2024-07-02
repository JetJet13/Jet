//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/ADT/APSInt.h>
#include <llvm/IR/Constants.h>
#include "bool-literal-ir-strategy.h"

IRBoolLiteralNode* BoolLiteralIRStrategy::generate(ASTBooleanLiteralNode* node, std::unique_ptr<llvm::LLVMContext>* context) {
    return node->getValue()
           ? new IRBoolLiteralNode(node, llvm::ConstantInt::get(**context, llvm::APSInt("1")))
           : new IRBoolLiteralNode(node, llvm::ConstantInt::get(**context, llvm::APSInt("0")));
}