//
// Created by Johny Georges on 2024-07-16.
//

#include "object-access-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-static-method-access-expression-node.h"
#include "../../../../../core/type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-method-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-instance-method-access-expression-node.h"


std::shared_ptr<IRExpressionNode> ObjectAccessExpressionIRStrategy::generate(std::shared_ptr<ASTObjectAccessExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    if (node->getSource()->getSource()->getTypeSignature()->typeSourceIs(CLASS_TYPE_SOURCE)) {
        auto classTypeSignature = std::dynamic_pointer_cast<ClassTypeSignature>(node->getSource()->getSource()->getTypeSignature());
        auto targetKey = node->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
        auto classStaticProperty = scope->findGlobalVariable(classTypeSignature->addClassNameToKey(targetKey));
        if (classStaticProperty) {
            return std::make_shared<IRClassStaticPropertyAccessExpressionNode>(node, classStaticProperty.value(), irType);
        }
        auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(node->getTypeSignature());
        auto methodId = classTypeSignature->addClassNameToKey(FunctionIdGenerator::generateFor(targetKey, invocableTypeSignature));
        auto classStaticMethod = scope->findAcrossScopes(methodId);
        return std::make_shared<IRClassStaticMethodAccessExpressionNode>(node, classStaticMethod.value(), irType);
    }

    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying());
    auto sourceType = sourceValue->getUnderlyingIRType();
    if (sourceType->isClassInstanceType()) {
        auto classInstanceTypeSignature = std::dynamic_pointer_cast<ClassInstanceTypeSignature>(node->getSource()->getSource()->getTypeSignature());
        auto classInstanceType = std::dynamic_pointer_cast<IRClassInstanceType>(sourceType);
        auto targetKey = node->getTarget()->getTarget()->getIdentifierNode()->getId();

        if (node->getTypeSignature()->isInvocable()) {
            auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(node->getTypeSignature());
            auto methodId = FunctionIdGenerator::generateFor(targetKey, invocableTypeSignature);
            auto classMethod = scope->findAcrossScopes(classInstanceTypeSignature->getClass()->addClassNameToKey(methodId));
            auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
            return std::make_shared<IRClassInstanceMethodAccessExpressionNode>(node, sourceValue, classMethod.value(), irType);
        }

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