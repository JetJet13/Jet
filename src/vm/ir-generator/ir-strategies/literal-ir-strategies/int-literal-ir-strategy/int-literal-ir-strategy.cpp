//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/ADT/APSInt.h>
#include <llvm/IR/Constants.h>
#include "int-literal-ir-strategy.h"

std::shared_ptr<IRIntLiteralNode> IntLiteralIRStrategy::generate(std::shared_ptr<ASTIntLiteralNode> node, IRContext* irContext) {
    return std::make_shared<IRIntLiteralNode>(node, llvm::ConstantInt::get(**irContext->getContext(), llvm::APInt(64, node->getValue(), 10)));
}