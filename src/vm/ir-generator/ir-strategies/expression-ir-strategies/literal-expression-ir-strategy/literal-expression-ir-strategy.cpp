//
// Created by Johny Georges on 2024-07-02.
//

#include "literal-expression-ir-strategy.h"


IRExpressionNode* LiteralExpressionIRStrategy::generate(ASTLiteralExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto irLiteralNode = irGenerator->generateFor(node->getLiteralNode(), scope, irContext);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    if (irLiteralNode->is(IR_STRING_LITERAL_NODE)) {
        auto stringLiteral = (IRStringLiteralNode*)irLiteralNode;
        auto arrayAllocation = this->generateArrayAllocation(stringLiteral, irGenerator, irContext, irOperation);
        auto arrayPointerAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType), arrayAllocation);
        return new IRStringLiteralExpressionNode(node, (IRStringLiteralNode*)irLiteralNode, (IRArrayPointerType*)irType, arrayAllocation, arrayPointerAllocation);
    }
    return new IRLiteralExpressionNode(node, irLiteralNode, irType);
}

IRInstructionNode* LiteralExpressionIRStrategy::generateArrayAllocation(IRStringLiteralNode* irStringLiteralNode, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation) {
    auto malloc = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocFunction(),
            { irGenerator->generateInt64Constant(irStringLiteralNode->getIRType()->getSizeInBytes()) },
            ""
    );
    return IRInstructionNodeFactory::create(
            malloc,
            irGenerator->generateIrPointerType(irStringLiteralNode->getIRType())
    );
}