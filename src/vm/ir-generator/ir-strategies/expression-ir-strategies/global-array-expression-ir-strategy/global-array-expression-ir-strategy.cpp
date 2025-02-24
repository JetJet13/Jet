//
// Created by Johny Georges on 2025-02-24.
//

#include "global-array-expression-ir-strategy.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../ir-type/ir-array-type.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRGlobalArrayExpressionNode* GlobalArrayExpressionIRStrategy::generate(ASTArrayExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
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
    auto mallocPointer = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFunction(),
            { irGenerator->generateIntConstant(arrayType->getSizeInBytes()) },
            ""
    );
    auto mallocAllocation = IRInstructionNodeFactory::create(mallocPointer, irGenerator->generateIrPointerType(arrayType), elementValueSourceAllocations);
    auto arrayPointerAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType), mallocAllocation);
    return new IRGlobalArrayExpressionNode(node, mallocAllocation, arrayPointerAllocation, elementValues, irType);
}