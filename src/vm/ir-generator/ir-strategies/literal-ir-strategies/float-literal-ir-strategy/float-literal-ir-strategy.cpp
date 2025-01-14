//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/ADT/APFloat.h>
#include "float-literal-ir-strategy.h"

IRFloatLiteralNode* FloatLiteralIRStrategy::generate(ASTFloatLiteralNode* node, IRContext* irContext) {
    return new IRFloatLiteralNode(node, llvm::ConstantFP::get(**irContext->getContext(), llvm::APFloat(node->getValue())));
}