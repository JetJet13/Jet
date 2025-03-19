//
// Created by Johny Georges on 2024-07-02.
//

#include "literal-expression-ir-strategy.h"


IRExpressionNode* LiteralExpressionIRStrategy::generate(ASTLiteralExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto irLiteralNode = irGenerator->generateFor(node->getLiteralNode(), scope, irContext);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    if (irLiteralNode->is(IR_STRING_LITERAL_NODE)) {
        auto stringLiteral = (IRStringLiteralNode*)irLiteralNode;
        auto arrayAllocation = new IRInstructionNode(
                this->generateArrayAllocation(stringLiteral, irGenerator, irContext, irOperationType),
                irGenerator->generateIrPointerType(irLiteralNode->getIRType())
        );
        auto arrayPointerAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType), arrayAllocation);
        return new IRStringLiteralExpressionNode(node, (IRStringLiteralNode*)irLiteralNode, (IRArrayPointerType*)irType, arrayAllocation, arrayPointerAllocation);
    }
    return new IRLiteralExpressionNode(node, irLiteralNode, irType);
}

llvm::Value* LiteralExpressionIRStrategy::generateArrayAllocation(IRStringLiteralNode* irStringLiteralNode, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType) {
    if (irOperationType == IR_COPY_GLOBAL_ASSIGNMENT_OP || irOperationType == IR_REF_GLOBAL_ASSIGNMENT_OP) {
        return llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction()->getFunctionType(),
                irContext->getIRModule()->getMallocFunction(),
                { irGenerator->generateIntConstant(irStringLiteralNode->getIRType()->getSizeInBytes()) },
                ""
        );
    }
    return new llvm::AllocaInst(
            irStringLiteralNode->getType(),
            AddressSpaceGenerator::generate(irStringLiteralNode->getIRType()->getElementType()),
            nullptr,
            DataAlignmentGenerator::generate(irStringLiteralNode->getIRType()->getElementType())
    );
}