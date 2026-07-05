//
// Created by Johny Georges on 2026-02-06.
//

#include "array-access-invocation-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-access-invocation-expression-node.h"

IRExpressionNode* ArrayAccessInvocationExpressionIRStrategy::generate(std::shared_ptr<ASTArrayAccessInvocationExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
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

    auto irExpression = (IRArrayAccessExpressionNode*)irGenerator->generateFor(node->getArrayAccess(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    auto irFunctionType = std::dynamic_pointer_cast<IRInvocableType>(irExpression->getIRType());
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto argList = irGenerator->generateArgumentPlaceholderList(irFunctionType, &arguments);
    auto callInstruction = llvm::CallInst::Create(irFunctionType->getFunctionType(), irExpression->getValue(), argList);
    return new IRArrayAccessInvocationExpressionNode(node, irExpression, callInstruction, irFunctionType, arguments, irReturnType);
}