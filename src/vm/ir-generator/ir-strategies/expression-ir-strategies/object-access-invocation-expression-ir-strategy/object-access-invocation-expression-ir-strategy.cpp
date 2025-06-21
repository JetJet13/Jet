//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-prototype-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-invocation-expression-node.h"

IRExpressionNode* ObjectAccessInvocationExpressionIRStrategy::generate(ASTObjectAccessInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        arguments.push_back(irGenerator->generateFor(argument, scope, irContext, IR_FUNCTION_ARGUMENT_OP));
    }

    if (node->isArrayPrototypeInvocation()) {
        auto irArrayExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, IR_OPERAND_OP);
        auto function = irContext->getModule()->getFunction(irGenerator->getArrayPrototypeFunctionName(node->getName()));
        auto irFunctionType = irGenerator->generateFunctionIrType(function->getFunctionType());
        auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
        return new IRArrayPrototypeInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType, irArrayExpression);
    }

    auto irExpression = (IRObjectAccessExpressionNode*)irGenerator->generateFor(node->getObjectAccess(), scope, irContext, IR_OPERAND_OP);
    auto irFunctionType = irExpression->getTargetIRType();
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    return new IRObjectAccessInvocationExpressionNode(node, irExpression, irFunctionType, arguments, irReturnType);

}