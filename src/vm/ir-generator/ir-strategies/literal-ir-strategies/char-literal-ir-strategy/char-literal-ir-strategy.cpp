//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/IR/Constants.h>
#include "char-literal-ir-strategy.h"

IRCharLiteralNode* CharLiteralIRStrategy::generate(ASTCharLiteralNode* node, IRGenerator* irGenerator, IRContext* irContext) {
    return new IRCharLiteralNode(node, irGenerator->generateChar(node->getValue()));
}