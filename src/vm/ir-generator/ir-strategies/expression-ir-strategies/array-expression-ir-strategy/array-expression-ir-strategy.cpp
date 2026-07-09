//
// Created by Johny Georges on 2024-06-17.
//

#include "array-expression-ir-strategy.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

std::shared_ptr<IRArrayExpressionNode> ArrayExpressionIRStrategy::generate(std::shared_ptr<ASTArrayExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto elementValues = std::vector<std::shared_ptr<IRExpressionNode>>();
    auto elementValueSourceAllocations = std::vector<std::shared_ptr<IRInstructionNode>>();
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
    return std::make_shared<IRArrayExpressionNode>(node, arrayAllocation, arrayPointerAllocation, elementValues, irType);
}

std::shared_ptr<IRInstructionNode> ArrayExpressionIRStrategy::generateArrayAllocation(std::shared_ptr<ASTArrayExpressionNode> node, std::shared_ptr<IRArrayPointerType> irArrayPointerType, std::shared_ptr<IRArrayType> irArrayType, std::shared_ptr<IRType> arrayElementIrType, std::vector<std::shared_ptr<IRInstructionNode>> childAllocations, IRGenerator* irGenerator, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
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

std::shared_ptr<IRInstructionNode> ArrayExpressionIRStrategy::generateArrayPointerAllocation(std::shared_ptr<ASTArrayExpressionNode> node, std::shared_ptr<IRArrayPointerType> irArrayPointerType, std::shared_ptr<IRArrayType> irArrayType, std::shared_ptr<IRInstructionNode> arrayAllocation, IRGenerator* irGenerator, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irArrayPointerType), arrayAllocation);
}