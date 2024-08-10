//
// Created by Johny Georges on 2024-07-16.
//

#include "object-access-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRObjectAccessExpressionNode* ObjectAccessExpressionIRStrategy::ObjectAccessExpressionIRStrategy::generate(ASTObjectAccessExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irModule);
    auto sourceType = (IRStructType*)sourceValue->getIRType()->getSourceType();
    auto targetKey = node->getTarget()->getTarget()->getIdentifierNode()->getId();
    auto targetIndex = sourceType->getIndexForKey(targetKey);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature());
    std::optional<IRInstructionNode*> sourceAllocation = {};
    if (irType->isArrayPointerType()) {
        if (sourceValue->is(IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE)) {
            sourceAllocation = IRInstructionNodeFactory::create(irGenerator->generatePointerType(sourceType->getIRTypeForKey(targetKey)));
        } else {
            // todo: figure out how to create source allocation for source array of struct expression field.
            sourceAllocation = IRInstructionNodeFactory::create(sourceValue->getSourceAllocationAtIndex(targetIndex).value());
            sourceValue
        }
//        sourceAllocation.value()->getIRType()->getSourceType()->print();
    }
    return new IRObjectAccessExpressionNode(node, sourceValue, targetKey, targetIndex, irGenerator->generateIntConstant(targetIndex), irType, sourceAllocation);
}