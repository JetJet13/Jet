//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/IR/Constants.h>
#include "char-literal-ir-strategy.h"

std::shared_ptr<IRCharLiteralNode> CharLiteralIRStrategy::generate(std::shared_ptr<ASTCharLiteralNode> node, IRGenerator* irGenerator, IRContext* irContext) {
    return std::make_shared<IRCharLiteralNode>(node, irGenerator->generateChar(node->getValue()));
}