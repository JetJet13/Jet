//
// Created by Johny Georges on 2024-11-08.
//

#include "function-invocation-expression-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRExpressionNode* FunctionInvocationExpressionIRStrategy::generate(ASTFunctionInvocationExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        arguments.push_back(irGenerator->generateFor(argument, scope, irModule, IR_FUNCTION_ARGUMENT_OP));
    }

    auto irFunctionType = irGenerator->generateTypeFor(node->getFunction()->getTypeSignature());
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature()->getReturnType());
    if (irFunctionType->isFunctionParameterType()) {
        auto irFunctionParameterType = (IRFunctionParameterType*)irFunctionType;
        auto function = scope->findLoaded(irFunctionParameterType->getFunctionParameterName(node->getFunction()->getId())).value()->getValue();
        auto functionScopeArgument = scope->findLoaded(irFunctionParameterType->getFunctionScopeArgumentParameterName(node->getFunction()->getId())).value()->getValue();
        return new IRFunctionParameterInvocationExpressionNode(node, function, functionScopeArgument, irFunctionParameterType, arguments, irReturnType);
    }

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

    auto function = irModule->getModule()->getFunction(node->getFunction()->getId());
    return new IRFunctionInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType, lambdaScopeArgument);
}