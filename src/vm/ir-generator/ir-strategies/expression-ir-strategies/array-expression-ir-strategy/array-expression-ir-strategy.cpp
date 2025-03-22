//
// Created by Johny Georges on 2024-06-17.
//

#include "array-expression-ir-strategy.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

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
    auto arrayType = new IRArrayType(llvm::ArrayType::get(arrayElementIrType->getType(), elementValues.size()), arrayElementIrType);
    auto arrayAllocation = new IRInstructionNode(
            this->generateArrayAllocation(node, arrayType, arrayElementIrType, irGenerator, irContext, irOperationType),
            irGenerator->generateIrPointerType(arrayType),
            elementValueSourceAllocations
    );
    auto arrayPointerAllocation = this->generateArrayPointerAllocation(node, arrayType, arrayAllocation, irGenerator, irContext, irOperationType);
    return new IRArrayExpressionNode(node, arrayAllocation, arrayPointerAllocation, elementValues, irType);
}

llvm::Value* ArrayExpressionIRStrategy::generateArrayAllocation(ASTArrayExpressionNode* node, IRArrayType* irArrayType, IRType* arrayElementIrType, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType) {
    if (node->isReferenced() || irOperationType == IR_COPY_GLOBAL_ASSIGNMENT_OP || irOperationType == IR_REF_GLOBAL_ASSIGNMENT_OP) {
        return llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction()->getFunctionType(),
                irContext->getIRModule()->getMallocFunction(),
                { irGenerator->generateIntConstant(irArrayType->getSizeInBytes()) },
                ""
        );
    }
    return new llvm::AllocaInst(
            irArrayType->getType(),
            AddressSpaceGenerator::generate(arrayElementIrType),
            nullptr,
            DataAlignmentGenerator::generate(arrayElementIrType)
    );
}

IRInstructionNode* ArrayExpressionIRStrategy::generateArrayPointerAllocation(ASTArrayExpressionNode* node, IRArrayType* irArrayType, IRInstructionNode* arrayAllocation, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType) {
    if (node->isReferenced() || irOperationType == IR_COPY_GLOBAL_ASSIGNMENT_OP || irOperationType == IR_REF_GLOBAL_ASSIGNMENT_OP) {
        return IRInstructionNodeFactory::create(
                llvm::CallInst::Create(
                    irContext->getIRModule()->getMallocFunction()->getFunctionType(),
                    irContext->getIRModule()->getMallocFunction(),
                    { irGenerator->generateIntConstant(irArrayType->getSizeInBytes()) },
                    ""
                ),
                irGenerator->generateIrPointerType(irArrayType),
                arrayAllocation
        );
    }
    return IRInstructionNodeFactory::create(
            irGenerator->generateIrPointerType(irArrayType), arrayAllocation);
}