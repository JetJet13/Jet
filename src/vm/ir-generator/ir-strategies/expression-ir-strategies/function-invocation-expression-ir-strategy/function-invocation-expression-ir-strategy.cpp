//
// Created by Johny Georges on 2024-11-08.
//

#include "function-invocation-expression-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRFunctionInvocationExpressionNode* FunctionInvocationExpressionIRStrategy::generate(ASTFunctionInvocationExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto lambdaScopeArgument = std::optional<IRInstructionNode*>();
    if (node->getFunction()->getTypeSignature()->typeSourceIs(LAMBDA_EXPRESSION_TYPE_SOURCE)) {
        auto lambdaTypeSignature = (LambdaExpressionTypeSignature*)node->getFunction()->getTypeSignature();
        auto lambdaScopeTypeSignature = (StructTypeSignature*)lambdaTypeSignature->getScopeParameter()->getTypeSignature();
        auto childAllocations = std::unordered_map<std::string, IRInstructionNode*>();
        for (const auto& keyValue : lambdaScopeTypeSignature->getKeyValuePairs()->getKeyValues()) {
            childAllocations[keyValue.first] = scope->find(keyValue.first).value();
        }
        auto irLambdaScopeType = irGenerator->generateTypeFor(lambdaTypeSignature->getScopeParameter()->getTypeSignature());
        lambdaScopeArgument = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irLambdaScopeType), childAllocations);
    }

    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        arguments.push_back(irGenerator->generateFor(argument, scope, irModule, IR_FUNCTION_ARGUMENT_OP));
    }

    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature()->getReturnType());
    auto irFunctionType = irGenerator->generateTypeFor(node->getFunction()->getTypeSignature());
    if (node->getFunction()->getTypeSignature()->isOneOf({ FUNCTION_LAMBDA_TYPE_SOURCE, PROCEDURE_LAMBDA_TYPE_SOURCE })) {
        auto function = scope->find(node->getFunction()->getId()).value()->getValue();
        auto pointerIRFunctionType = (IRPointerType*)irFunctionType;
        return new IRFunctionInvocationExpressionNode(node, function, (IRFunctionType*)pointerIRFunctionType->getSourceType(), arguments, irReturnType, lambdaScopeArgument);
    } else {
        auto function = irModule->getModule()->getFunction(node->getFunction()->getId());
        return new IRFunctionInvocationExpressionNode(node, function, (IRFunctionType*)irFunctionType, arguments, irReturnType, lambdaScopeArgument);
    }
}