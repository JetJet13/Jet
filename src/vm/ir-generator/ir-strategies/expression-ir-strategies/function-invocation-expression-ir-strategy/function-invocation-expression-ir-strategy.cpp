//
// Created by Johny Georges on 2024-11-08.
//

#include "function-invocation-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../ir-type/ir-lambda-type.h"

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

    auto irFunctionType = (IRFunctionType*)irGenerator->generateTypeFor(node->getFunction()->getTypeSignature(), scope, irContext);
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature()->getReturnType(), scope, irContext);

    // generate placeholder arg list for call instruction
    auto argList = this->generatePlaceholderArgumentList(node, irFunctionType, irGenerator, irContext);
    if (irFunctionType->isFunctionParameterType() || irFunctionType->isLambdaType()) {
        auto function = scope->find(node->getFunction()->getId()).value()->getValue();
        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, argList);
        return new IRFunctionInvocationExpressionNode(node, function, callInstruction, irFunctionType, arguments, irReturnType, varArgsTypeValueArgument);
    }

    if (node->getFunction()->getTypeSignature()->isBuiltIn()) {
        auto irFunctionName = irGenerator->getJetUtilsFunctionName(node->getFunction()->getId());
        auto function = irContext->getModule()->getFunction(irFunctionName);
        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, argList);
        return new IRFunctionInvocationExpressionNode(node, function, callInstruction, irFunctionType, arguments, irReturnType, varArgsTypeValueArgument);
    }

    auto function = irContext->getModule()->getFunction(node->getFunction()->getId());
    auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, argList);
    return new IRFunctionInvocationExpressionNode(node, function, callInstruction, irFunctionType, arguments, irReturnType, varArgsTypeValueArgument);
}

std::vector<llvm::Value*> FunctionInvocationExpressionIRStrategy::generatePlaceholderArgumentList(ASTFunctionInvocationExpressionNode* node, IRFunctionType* irFunctionType, IRGenerator* irGenerator, IRContext* irContext) {
    auto pointerType = irGenerator->generatePointerType();
    auto argList = std::vector<llvm::Value*>();
    auto numArguments = node->getTypeSignature()->getFunctionType()->hasVariableLengthParameters() ?
            node->getArguments()->numArguments()
            : irFunctionType->getType()->getNumParams();
    for (int i = 0; i < numArguments; ++i) {
        argList.push_back(llvm::ConstantPointerNull::get(pointerType));
    }

    if (irFunctionType->isLambdaType()) {
        auto irLambdaType = (IRLambdaType*)irFunctionType;
        if (irLambdaType->getLambdaScopeType() && irLambdaType->getLambdaScopeType().value()->size() > 0) {
            argList.push_back(llvm::ConstantPointerNull::get(pointerType));
        }
    }

    if (irFunctionType->isFunctionParameterType()) {
        argList.push_back(llvm::ConstantPointerNull::get(pointerType));
    }

    if (node->getTypeSignature()->getFunctionType()->hasVariableLengthParameters()) {
        argList.push_back(llvm::ConstantPointerNull::get(pointerType));
    }

    if (node->getTypeSignature()->getFunctionType()->isOneOfBuiltInTypeSources({ BI_ASSERT_TYPE_SOURCE, BI_ASSERT_WITH_MESSAGE_TYPE_SOURCE })) {
        auto assertMessage = irGenerator->getOrInsertGlobalVariableString(node->getId(), "(" + node->getLineColumn() + ") " + node->toSourceCode() + "\n\n", irContext);
        argList.push_back(assertMessage);
    }

    return argList;
}