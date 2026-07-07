//
// Created by Johny Georges on 2026-02-06.
//

#include "array-access-invocation-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-access-invocation-expression-node.h"

std::shared_ptr<IRExpressionNode> ArrayAccessInvocationExpressionIRStrategy::generate(std::shared_ptr<ASTArrayAccessInvocationExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, std::shared_ptr<IROperation> irOperation) {
    auto arguments = std::vector<std::shared_ptr<IRFunctionArgumentNode>>();
    for (int i = 0; i < node->getArguments()->numArguments(); ++i) {
        auto argument = node->getArguments()->getArguments()->at(i);
        arguments.push_back(
            irGenerator->generateFor(
                argument,
                i,
                scope,
                irContext,
                std::make_shared<IROperation>(IR_FUNCTION_ARGUMENT_OP),
                node->getInvocableTypeSignature()
            )
        );
    }

    auto irExpression = std::dynamic_pointer_cast<IRArrayAccessExpressionNode>(irGenerator->generateFor(node->getArrayAccess(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP)));
    auto irFunctionType = std::dynamic_pointer_cast<IRInvocableType>(irExpression->getIRType());
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto argList = irGenerator->generateArgumentPlaceholderList(irFunctionType, &arguments);
    auto callInstruction = llvm::CallInst::Create(irFunctionType->getFunctionType(), irExpression->getValue(), argList);
    return std::make_shared<IRArrayAccessInvocationExpressionNode>(node, irExpression, callInstruction, irFunctionType, arguments, irReturnType);
}