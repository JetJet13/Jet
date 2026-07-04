//
// Created by Johny Georges on 2024-06-15.
//

#include "float-literal-ir-strategy.h"

IRFloatLiteralNode* FloatLiteralIRStrategy::generate(std::shared_ptr<ASTFloatLiteralNode> node, IRGenerator* irGenerator, IRContext* irContext) {
    return new IRFloatLiteralNode(
            node,
            llvm::ConstantFP::get(
                **irContext->getContext(),
                llvm::APFloat(llvm::APFloat::IEEEdouble(), node->getValue())
            )
    );
}