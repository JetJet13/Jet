//
// Created by Johny Georges on 2024-07-16.
//

#include "object-access-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRObjectAccessExpressionNode* ObjectAccessExpressionIRStrategy::generate(ASTObjectAccessExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irModule, irOperationType);
    auto sourceType = (IRStructType*)sourceValue->getIRType()->getSourceType();
    auto targetKey = node->getTarget()->getTarget()->getIdentifierNode()->getId();
    auto targetIndex = sourceType->getIndexForKey(targetKey);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope);
    auto sourceAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
    if (irType->isArrayPointerType()) {
        sourceAllocation->setParentAllocation(
            IRInstructionNodeFactory::create(
                    irGenerator->generateIrPointerType(sourceType->getIRTypeByIndex(targetIndex)))
        );
    }
    return new IRObjectAccessExpressionNode(node, sourceValue, targetKey, targetIndex, irGenerator->generateIntConstant(targetIndex), irType, sourceAllocation);
}