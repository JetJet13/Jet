//
// Created by Johny Georges on 2024-07-02.
//

#include "literal-expression-ir-strategy.h"


std::shared_ptr<IRExpressionNode> LiteralExpressionIRStrategy::generate(std::shared_ptr<ASTLiteralExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto irLiteralNode = irGenerator->generateFor(node->getLiteralNode(), scope, irContext);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    if (irLiteralNode->is(IR_STRING_LITERAL_NODE)) {
        auto stringLiteral = std::dynamic_pointer_cast<IRStringLiteralNode>(irLiteralNode);
        auto arrayAllocation = this->generateArrayAllocation(stringLiteral, irGenerator, irContext, irOperation);
        auto arrayPointerAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType), arrayAllocation);
        return std::make_shared<IRStringLiteralExpressionNode>(node, std::dynamic_pointer_cast<IRStringLiteralNode>(irLiteralNode), std::dynamic_pointer_cast<IRArrayPointerType>(irType), arrayAllocation, arrayPointerAllocation);
    }
    return std::make_shared<IRLiteralExpressionNode>(node, irLiteralNode, irType);
}

std::shared_ptr<IRInstructionNode> LiteralExpressionIRStrategy::generateArrayAllocation(std::shared_ptr<IRStringLiteralNode> irStringLiteralNode, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto malloc = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocFunction(),
            {
                irGenerator->generateInt64Constant(irStringLiteralNode->getIRArrayType()->getSize()),
                irGenerator->generateInt64Constant(irStringLiteralNode->getIRArrayType()->getElementIRType()->getSizeInBytes())
            },
            ""
    );
    return IRInstructionNodeFactory::create(
            malloc,
            irGenerator->generateIrPointerType(irStringLiteralNode->getIRType())
    );
}