//
// Created by Johny Georges on 2024-06-17.
//

#include "array-expression-ir-strategy.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRArrayExpressionNode* ArrayExpressionIRStrategy::generate(ASTArrayExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto elementValues = std::vector<IRExpressionNode*>();
    for (auto element : *node->getElements()) {
        elementValues.push_back(irGenerator->generateFor(element, scope, irModule));
    }
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature());
    auto arrayElementIrType = irGenerator->generateTypeFor(node->getTypeSignature()->getElementType());
    auto arrayAllocation = IRInstructionNodeFactory::createForArray(arrayElementIrType, irType, node->size());
    irType->setSourceType(new IRType(arrayAllocation->getValue()->getAllocatedType()));
    return new IRArrayExpressionNode(node, arrayAllocation, elementValues, irGenerator->generateTypeFor(node->getTypeSignature()));
}