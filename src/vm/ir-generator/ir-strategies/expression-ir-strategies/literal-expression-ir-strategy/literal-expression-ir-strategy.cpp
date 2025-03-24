//
// Created by Johny Georges on 2024-07-02.
//

#include "literal-expression-ir-strategy.h"


IRExpressionNode* LiteralExpressionIRStrategy::generate(ASTLiteralExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto irLiteralNode = irGenerator->generateFor(node->getLiteralNode(), scope, irContext);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    if (irLiteralNode->is(IR_STRING_LITERAL_NODE)) {
        auto stringLiteral = (IRStringLiteralNode*)irLiteralNode;
        auto arrayAllocation = this->generateArrayAllocation(stringLiteral, irGenerator, irContext, irOperationType);
        auto arrayPointerAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType), arrayAllocation);
        return new IRStringLiteralExpressionNode(node, (IRStringLiteralNode*)irLiteralNode, (IRArrayPointerType*)irType, arrayAllocation, arrayPointerAllocation);
    }
    return new IRLiteralExpressionNode(node, irLiteralNode, irType);
}

IRInstructionNode* LiteralExpressionIRStrategy::generateArrayAllocation(IRStringLiteralNode* irStringLiteralNode, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType) {
    if (irOperationType == IR_COPY_GLOBAL_ASSIGNMENT_OP || irOperationType == IR_REF_GLOBAL_ASSIGNMENT_OP) {
        auto malloc = llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction()->getFunctionType(),
                irContext->getIRModule()->getMallocFunction(),
                { irGenerator->generateIntConstant(irStringLiteralNode->getIRType()->getSizeInBytes()) },
                ""
        );
        return IRInstructionNodeFactory::create(
                new llvm::BitCastInst(malloc, irStringLiteralNode->getIRType()->getType()),
                irGenerator->generateIrPointerType(irStringLiteralNode->getIRType()),
                { malloc }
        );
    }
    return IRInstructionNodeFactory::create(
            new llvm::AllocaInst(
                    irStringLiteralNode->getType(),
                    AddressSpaceGenerator::generate(irStringLiteralNode->getIRType()->getElementType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irStringLiteralNode->getIRType()->getElementType())
            ),
            irGenerator->generateIrPointerType(irStringLiteralNode->getIRType())
    );
}