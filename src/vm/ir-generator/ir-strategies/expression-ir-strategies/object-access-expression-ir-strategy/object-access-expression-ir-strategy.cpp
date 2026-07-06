//
// Created by Johny Georges on 2024-07-16.
//

#include "object-access-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../ir-type/ir-class-instance-type.h"


std::shared_ptr<IRExpressionNode> ObjectAccessExpressionIRStrategy::generate(std::shared_ptr<ASTObjectAccessExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, IROperation* irOperation) {
    if (node->getSource()->getSource()->getTypeSignature()->typeSourceIs(CLASS_TYPE_SOURCE)) {
        auto classTypeSignature = std::dynamic_pointer_cast<ClassTypeSignature>(node->getSource()->getSource()->getTypeSignature());
        auto targetKey = classTypeSignature->addClassNameToKey(node->getTarget()->getTarget()->getIdentifierNode()->getId());
        auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
        auto classStaticProperty = scope->findGlobalVariable(targetKey);
        return std::make_shared<IRClassStaticPropertyAccessExpressionNode>(node, classStaticProperty.value(), irType);
    }

    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying());
    auto sourceType = sourceValue->getUnderlyingIRType();
    if (sourceType->isClassInstanceType()) {
        auto classInstanceType = std::dynamic_pointer_cast<IRClassInstanceType>(sourceType);
        auto targetKey = node->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto targetIndex = classInstanceType->getIndexForProperty(targetKey);
        auto irType = classInstanceType->getIRTypeForProperty(targetKey);
        auto sourceAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
        return std::make_shared<IRObjectAccessExpressionNode>(node, sourceValue, targetKey, targetIndex, irGenerator->generateIntConstant(targetIndex), irType, sourceAllocation);
    } else if (sourceType->isStructRefType()) {
        auto structRefType = std::dynamic_pointer_cast<IRStructRefType>(sourceType);
        auto targetKey = node->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto targetIndex = structRefType->getStructIRType()->getIndexForKey(targetKey);
        auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
        auto sourceAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
        return std::make_shared<IRObjectAccessExpressionNode>(node, sourceValue, targetKey, targetIndex, irGenerator->generateIntConstant(targetIndex), irType, sourceAllocation);
    } else {
        auto structType = std::dynamic_pointer_cast<IRStructType>(sourceType);
        auto targetKey = node->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto targetIndex = structType->getIndexForKey(targetKey);
        auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
        auto sourceAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
        return std::make_shared<IRObjectAccessExpressionNode>(node, sourceValue, targetKey, targetIndex, irGenerator->generateIntConstant(targetIndex), irType, sourceAllocation);
    }
}