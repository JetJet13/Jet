//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/IR/Constants.h>
#include "char-literal-ir-strategy.h"

IRCharLiteralNode* CharLiteralIRStrategy::generate(ASTCharLiteralNode* node, IRContext* irContext) {
    return new IRCharLiteralNode(node, llvm::ConstantInt::get(**irContext->getContext(), llvm::APInt(CHAR_BIT, node->getValue())));
}