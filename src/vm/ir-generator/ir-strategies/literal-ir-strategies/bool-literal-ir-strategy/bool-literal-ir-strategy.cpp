//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/ADT/APSInt.h>
#include <llvm/IR/Constants.h>
#include "bool-literal-ir-strategy.h"

IRBoolLiteralNode* BoolLiteralIRStrategy::generate(std::shared_ptr<ASTBooleanLiteralNode> node, IRContext* irContext) {
    return node->getValue()
           ? new IRBoolLiteralNode(node, llvm::ConstantInt::get(**irContext->getContext(), llvm::APSInt("1")))
           : new IRBoolLiteralNode(node, llvm::ConstantInt::get(**irContext->getContext(), llvm::APSInt("0")));
}