//
// Created by Johny Georges on 2024-11-08.
//

#include "function-invocation-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRExpressionNode* FunctionInvocationExpressionIRStrategy::generate(ASTFunctionInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (int i = 0; i < node->getArguments()->numArguments(); ++i) {
        auto argument = irGenerator->generateFor(
                node->getArguments()->getArguments()->at(i),
                scope,
                irContext,
                new IROperation(IR_FUNCTION_ARGUMENT_OP)
        );
        arguments.push_back(argument);
    }

    std::optional<IRInstructionNode*> varArgsTypeValueArgument = {};
    if (node->getTypeSignature()->getFunctionType()->hasVariableLengthParameters()) {
        auto startIndex = node->getTypeSignature()->getFunctionType()->getVariableLengthParametersStartIndex();
        auto numVarArgs = arguments.size() - startIndex;
        varArgsTypeValueArgument = IRInstructionNodeFactory::create(
            irGenerator->generateIrArrayPointerType(irGenerator->generateIrTypeValueType()),
            IRInstructionNodeFactory::create(
                irGenerator->generateIrPointerType(irGenerator->generateIrTypeValueType()),
                irGenerator->generateIntConstant(numVarArgs)
            )
        );
    }

    auto irFunctionType = irGenerator->generateTypeFor(node->getFunction()->getTypeSignature(), scope, irContext);
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature()->getReturnType(), scope, irContext);
    if (irFunctionType->isFunctionParameterType() || irFunctionType->isLambdaType()) {
        auto function = scope->find(node->getFunction()->getId()).value()->getValue();
        return new IRFunctionInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType, varArgsTypeValueArgument);
    }

    if (node->getFunction()->getTypeSignature()->isBuiltIn()) {
        Logger::log("built-in!", node->getFunction()->getId());
        node->getFunction()->getTypeSignature()->print();
        node->print();
        auto irFunctionName = irGenerator->getJetUtilsFunctionName(node->getFunction()->getId());
        auto function = irContext->getModule()->getFunction(irFunctionName);
        return new IRFunctionInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType, varArgsTypeValueArgument);
    }

    auto function = irContext->getModule()->getFunction(node->getFunction()->getId());
    return new IRFunctionInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType, varArgsTypeValueArgument);
}