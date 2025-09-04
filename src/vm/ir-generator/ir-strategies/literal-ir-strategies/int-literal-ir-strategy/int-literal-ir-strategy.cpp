//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/ADT/APSInt.h>
#include <llvm/IR/Constants.h>
#include "int-literal-ir-strategy.h"

IRIntLiteralNode* IntLiteralIRStrategy::generate(ASTIntLiteralNode* node, IRContext* irContext) {
    return new IRIntLiteralNode(node, llvm::ConstantInt::get(**irContext->getContext(), llvm::APInt(64, node->getValue())));
}