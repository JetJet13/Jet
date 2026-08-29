//
// Created by Johny Georges on 2024-12-14.
//

#include "class-property-access-expression-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-method-access-expression-node.h"

std::shared_ptr<IRExpressionNode> ClassPropertyAccessExpressionIRStrategy::generate(std::shared_ptr<ASTClassPropertyAccessExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto classScope = scope->getClassScope().value();
    auto sourceType = std::dynamic_pointer_cast<IRStructRefType>(classScope->getIRType()->getUnderlyingType());
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto targetKey = node->getPropertyName();
    if (node->getTypeSignature()->isInvocable()) {
        auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(node->getTypeSignature());
        auto irInvocableType = std::dynamic_pointer_cast<IRInvocableType>(irType);
        auto classTypeSignature = node->getPropertyAccess()->getClassAccess()->getClassTypeSignature();
        auto methodId = classTypeSignature->addClassNameToKey(FunctionIdGenerator::generateFor(targetKey, invocableTypeSignature));
        auto irMethod = scope->findAcrossScopes(methodId);
        return std::make_shared<IRClassMethodAccessExpressionNode>(node, irMethod.value(), irInvocableType);
    }
    auto targetIndex = sourceType->getStructIRType()->getIndexForKey(targetKey);
    return std::make_shared<IRClassPropertyAccessExpressionNode>(node, classScope, targetKey, targetIndex, irGenerator->generateIntConstant(targetIndex), irType);
}