//
// Created by Johny Georges on 2025-06-18.
//

#include "tuple-access-invocation-expression-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-tuple-access-invocation-expression-node.h"

IRExpressionNode* TupleAccessInvocationExpressionIRStrategy::generate(ASTTupleAccessInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto arguments = std::vector<IRFunctionArgumentNode*>();
    for (int i = 0; i < node->getArguments()->numArguments(); ++i) {
        auto argument = node->getArguments()->getArguments()->at(i);
        arguments.push_back(
            irGenerator->generateFor(
                argument,
                i,
                scope,
                irContext,
                new IROperation(IR_FUNCTION_ARGUMENT_OP),
                node->getInvocableTypeSignature()
            )
        );
    }

    auto irExpression = (IRTupleAccessExpressionNode*)irGenerator->generateFor(node->getObjectAccess(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    auto irFunctionType = (IRFunctionType*)irExpression->getTargetIRType();
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto argList = irGenerator->generateArgumentPlaceholderList(irFunctionType, &arguments);
    auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), irExpression->getValue(), argList);
    return new IRTupleAccessInvocationExpressionNode(node, irExpression, callInstruction, irFunctionType, arguments, irReturnType);
}