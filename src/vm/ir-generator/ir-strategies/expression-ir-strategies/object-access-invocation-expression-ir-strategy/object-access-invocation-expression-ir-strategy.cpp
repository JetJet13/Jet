//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-prototype-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-invocation-expression-node.h"
#include "../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../ir-type/ir-class-instance-type.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-ref-prototype-invocation-expression-node.h"

IRExpressionNode* ObjectAccessInvocationExpressionIRStrategy::generate(ASTObjectAccessInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        arguments.push_back(irGenerator->generateFor(argument, scope, irContext, new IROperation(IR_FUNCTION_ARGUMENT_OP)));
    }

    if (node->isArrayPrototypeInvocation()) {
        auto irArrayExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, new IROperation(IR_OPERAND_POINTER_OP));
        auto function = irContext->getModule()->getFunction(irGenerator->getArrayPrototypeFunctionName(node->getName()));
        auto irFunctionType = irGenerator->generateFunctionIrType(function->getFunctionType());
        auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
        return new IRArrayPrototypeInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType, irArrayExpression);
    }

    if (node->isRefPrototypeInvocation()) {
        auto irRefExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, new IROperation(IR_OPERAND_POINTER_OP));
        auto function = irContext->getModule()->getFunction(irGenerator->getRefPrototypeFunctionName(node->getName()));
        auto irFunctionType = irGenerator->generateFunctionIrType(function->getFunctionType());
        auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
        return new IRRefPrototypeInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType, irRefExpression);
    }

    auto functionId = FunctionIdGenerator::generateFor(node);
    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying());
    auto sourceType = sourceValue->getUnderlyingIRType();
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    if (sourceType->isClassInstanceType()) {
        auto classInstanceType = (IRClassInstanceType*)sourceType;
        auto irFunctionType = classInstanceType->getIRTypeForMethod(functionId).value();
        auto irFunction = irContext->getModule()->getFunction(classInstanceType->getIRMethodName(functionId));
        return new IRObjectAccessInvocationExpressionNode(node, irFunction, irFunctionType, arguments, irReturnType, sourceValue);
    }

    auto irStructType = (IRStructType*)sourceType;
    auto irFunctionType = irStructType->getIRTypeForKey(functionId);
    auto irFunction = irContext->getModule()->getFunction(functionId);
    return new IRObjectAccessInvocationExpressionNode(node, irFunction, irFunctionType, arguments, irReturnType);
}