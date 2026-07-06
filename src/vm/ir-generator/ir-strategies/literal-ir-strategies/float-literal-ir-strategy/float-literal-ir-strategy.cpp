//
// Created by Johny Georges on 2024-06-15.
//

#include "float-literal-ir-strategy.h"

std::shared_ptr<IRFloatLiteralNode> FloatLiteralIRStrategy::generate(std::shared_ptr<ASTFloatLiteralNode> node, IRGenerator* irGenerator, IRContext* irContext) {
    return std::make_shared<IRFloatLiteralNode>(
            node,
            llvm::ConstantFP::get(
                **irContext->getContext(),
                llvm::APFloat(llvm::APFloat::IEEEdouble(), node->getValue())
            )
    );
}