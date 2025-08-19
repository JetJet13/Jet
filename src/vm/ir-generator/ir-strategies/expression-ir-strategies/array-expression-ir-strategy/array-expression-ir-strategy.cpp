//
// Created by Johny Georges on 2024-06-17.
//

#include "array-expression-ir-strategy.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRArrayExpressionNode* ArrayExpressionIRStrategy::generate(ASTArrayExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto elementValues = std::vector<IRExpressionNode*>();
    auto elementValueSourceAllocations = std::vector<IRInstructionNode*>();
    for (auto element : *node->getElements()) {
        auto elementIrExpression = irGenerator->generateFor(element, scope, irContext, irOperationType);
        elementValues.push_back(elementIrExpression);
        if (elementIrExpression->getSourceAllocation()) {
            elementValueSourceAllocations.push_back(elementIrExpression->getSourceAllocation().value());
        }
    }
    auto arrayElementIrType = irGenerator->generateTypeFor(node->getTypeSignature()->getElementType(), scope, irContext);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto arrayType = irGenerator->generateIRArrayType(arrayElementIrType, node->getElements()->size());
    auto arrayAllocation = this->generateArrayAllocation(node, irType, arrayType, arrayElementIrType, elementValueSourceAllocations, irGenerator, irContext, irOperationType);
    auto arrayPointerAllocation = this->generateArrayPointerAllocation(node, irType, arrayType, arrayAllocation, irGenerator, irContext, irOperationType);
    if (!arrayPointerAllocation->getParentAllocation()) {
        throw std::logic_error("arrayPointerAllocation has no parent allocation");
    }
    return new IRArrayExpressionNode(node, arrayAllocation, arrayPointerAllocation, elementValues, irType);
}

IRInstructionNode* ArrayExpressionIRStrategy::generateArrayAllocation(ASTArrayExpressionNode* node, IRArrayPointerType* irArrayPointerType, IRArrayType* irArrayType, IRType* arrayElementIrType, std::vector<IRInstructionNode*> childAllocations, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType) {
    auto malloc = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFunction(),
            { irGenerator->generateInt64Constant(irArrayType->get8BitAlignedSizeInBytes()) },
            ""
    );
    return IRInstructionNodeFactory::create(
            malloc,
            irGenerator->generateIrPointerType(irArrayType),
            std::move(childAllocations)
    );
}

IRInstructionNode* ArrayExpressionIRStrategy::generateArrayPointerAllocation(ASTArrayExpressionNode* node, IRArrayPointerType* irArrayPointerType, IRArrayType* irArrayType, IRInstructionNode* arrayAllocation, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType) {
    auto malloc = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFunction(),
            { irGenerator->generateInt64Constant(irArrayPointerType->get8BitAlignedSizeInBytes()) }
    );
    return IRInstructionNodeFactory::create(
            malloc,
            irGenerator->generateIrPointerType(irArrayPointerType),
            arrayAllocation
    );
}