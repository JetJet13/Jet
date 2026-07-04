//
// Created by Johny Georges on 2024-06-17.
//

#include "array-expression-ir-strategy.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRArrayExpressionNode* ArrayExpressionIRStrategy::generate(std::shared_ptr<ASTArrayExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto elementValues = std::vector<IRExpressionNode*>();
    auto elementValueSourceAllocations = std::vector<IRInstructionNode*>();
    for (auto element : *node->getElements()) {
        auto elementIrExpression = irGenerator->generateFor(element, scope, irContext, irOperation);
        elementIrExpression->markAsAssigned();
        elementValues.push_back(elementIrExpression);
        if (elementIrExpression->getSourceAllocation()) {
            elementValueSourceAllocations.push_back(elementIrExpression->getSourceAllocation().value());
        }
    }
    auto arrayElementIrType = irGenerator->generateTypeFor(node->getArrayTypeSignature()->getElementType(), scope, irContext);
    auto irType = irGenerator->generateTypeFor(node->getArrayTypeSignature(), scope, irContext);
    auto arrayType = irGenerator->generateIRArrayType(arrayElementIrType, node->getElements()->size());
    auto arrayAllocation = this->generateArrayAllocation(node, irType, arrayType, arrayElementIrType, elementValueSourceAllocations, irGenerator, irContext, irOperation);
    auto arrayPointerAllocation = this->generateArrayPointerAllocation(node, irType, arrayType, arrayAllocation, irGenerator, irContext, irOperation);
    return new IRArrayExpressionNode(node, arrayAllocation, arrayPointerAllocation, elementValues, irType);
}

IRInstructionNode* ArrayExpressionIRStrategy::generateArrayAllocation(std::shared_ptr<ASTArrayExpressionNode> node, IRArrayPointerType* irArrayPointerType, IRArrayType* irArrayType, IRType* arrayElementIrType, std::vector<IRInstructionNode*> childAllocations, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation) {
    auto malloc = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocFunction(),
            {
                irGenerator->generateInt64Constant(irArrayType->getSize()),
                irGenerator->generateInt64Constant(irArrayType->getElementIRType()->getSizeInBytes())
            },
            ""
    );
    return IRInstructionNodeFactory::create(
            malloc,
            irGenerator->generateIrPointerType(irArrayType),
            std::move(childAllocations)
    );
}

IRInstructionNode* ArrayExpressionIRStrategy::generateArrayPointerAllocation(std::shared_ptr<ASTArrayExpressionNode> node, IRArrayPointerType* irArrayPointerType, IRArrayType* irArrayType, IRInstructionNode* arrayAllocation, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation) {
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irArrayPointerType), arrayAllocation);
}