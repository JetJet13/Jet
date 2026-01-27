//
// Created by Johny Georges on 2024-11-08.
//

#include "function-invocation-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRExpressionNode* FunctionInvocationExpressionIRStrategy::generate(ASTFunctionInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (unsigned long i = 0; i < node->getArguments()->numArguments(); ++i) {
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

    auto irType = irGenerator->generateTypeFor(node->getFunction()->getTypeSignature(), scope, irContext);
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature()->getReturnType(), scope, irContext);

    if (irType->isInvocableType()) {
        auto irInvocableType = (IRInvocableType*)irType;
        auto source = scope->findAcrossScopes(node->getFunction()->getId()).value();
        auto argList = this->prepArgumentList(node, irInvocableType, irGenerator, irContext);
        auto callInstruction = llvm::CallInst::Create(irInvocableType->getIRFunctionType()->getType(), source->getValue(), argList);
        return new IRFunctionInvocationExpressionNode(node, source, callInstruction, irType, arguments, irReturnType, varArgsTypeValueArgument);
    }

    if (node->getFunction()->getTypeSignature()->isBuiltIn()) {
        auto irFunctionType = (IRFunctionType*)irType;
        auto irFunctionName = node->getFunction()->getTypeSignature()->isDebug()
                ? irGenerator->getJetDebugFunctionName(node->getFunction()->getId())
                : irGenerator->getJetUtilsFunctionName(node->getFunction()->getId());
        auto function = irContext->getModule()->getFunction(irFunctionName);
        auto irFunction = IRInstructionNodeFactory::create(function, irGenerator->generateIrPointerType(irFunctionType));
        auto argList = this->prepArgumentList(node, irFunctionType, irGenerator, irContext);
        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, argList);
        return new IRFunctionInvocationExpressionNode(node, irFunction, callInstruction, irType, arguments, irReturnType, varArgsTypeValueArgument);
    }

    auto irFunctionType = (IRFunctionType*)irType;
    auto function = irContext->getModule()->getFunction(node->getFunction()->getId());
    auto irFunction = IRInstructionNodeFactory::create(function, irGenerator->generateIrPointerType(irFunctionType));
    auto argList = this->prepArgumentList(node, irFunctionType, irGenerator, irContext);
    auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, argList);
    return new IRFunctionInvocationExpressionNode(node, irFunction, callInstruction, irType, arguments, irReturnType, varArgsTypeValueArgument);
}

std::vector<llvm::Value*> FunctionInvocationExpressionIRStrategy::prepArgumentList(ASTFunctionInvocationExpressionNode* node, IRFunctionType* irFunctionType, IRGenerator* irGenerator, IRContext* irContext) {
    auto pointerType = irGenerator->generatePointerType();
    auto argList = std::vector<llvm::Value*>();
    auto numArguments = node->getTypeSignature()->getFunctionType()->hasVariableLengthParameters() ?
            node->getArguments()->numArguments()
            : irFunctionType->getType()->getNumParams();
    for (unsigned long i = 0; i < numArguments; ++i) {
        argList.push_back(llvm::ConstantPointerNull::get(pointerType));
    }

    if (node->getTypeSignature()->getFunctionType()->hasVariableLengthParameters()) {
        argList.push_back(llvm::ConstantPointerNull::get(pointerType));
    }

    if (node->getTypeSignature()->getFunctionType()->isOneOfBuiltInTypeSources({
            BI_ASSERT_TYPE_SOURCE,
            BI_ASSERT_WITH_MESSAGE_TYPE_SOURCE,
            BI_ASSERT_DEBUG_LAMBDA_REF_COUNT_TYPE_SOURCE,
            BI_ASSERT_DEBUG_REF_COUNT_TYPE_SOURCE,
            BI_ASSERT_DEBUG_STRUCT_REF_COUNT_TYPE_SOURCE
    })) {
        auto assertMessage = irGenerator->getOrInsertGlobalVariableString(node->getId(), "(" + node->getLineColumn() + ") " + node->toSourceCode() + "\n\n", irContext);
        argList.push_back(assertMessage);
    }

    return argList;
}

std::vector<llvm::Value*> FunctionInvocationExpressionIRStrategy::prepArgumentList(ASTFunctionInvocationExpressionNode* node, IRInvocableType* irInvocableType, IRGenerator* irGenerator, IRContext* irContext) {
    auto pointerType = irGenerator->generatePointerType();
    auto argList = std::vector<llvm::Value*>();
    auto numArguments = irInvocableType->getFunctionType()->getNumParams();
    for (unsigned long i = 0; i < numArguments; ++i) {
        argList.push_back(llvm::ConstantPointerNull::get(pointerType));
    }

    // for lambda scope argument;
    argList.push_back(llvm::ConstantPointerNull::get(pointerType));

    return argList;
}