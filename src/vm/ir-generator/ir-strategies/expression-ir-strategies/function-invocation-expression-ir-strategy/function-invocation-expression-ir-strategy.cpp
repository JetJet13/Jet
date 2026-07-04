//
// Created by Johny Georges on 2024-11-08.
//

#include "function-invocation-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../../shared/utils/function-id-generator/function-id-generator.h"

IRExpressionNode* FunctionInvocationExpressionIRStrategy::generate(std::shared_ptr<ASTFunctionInvocationExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto arguments = std::vector<IRFunctionArgumentNode*>();
    for (unsigned long i = 0; i < node->getArguments()->numArguments(); ++i) {
        arguments.push_back(
                irGenerator->generateFor(
                        node->getArguments()->getArguments()->at(i),
                        i,
                        scope,
                        irContext,
                        new IROperation(IR_FUNCTION_ARGUMENT_OP),
                        node->getTypeSignature()->getFunctionType()
                )
        );
    }
    auto argList = irGenerator->generateArgumentPlaceholderListForFunction(node->getTypeSignature()->getFunctionType(), &arguments, scope, irContext);

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
        auto source = scope->findAcrossScopes(node->getFunction()->getModuleId(), node->getFunction()->getId()).value();
        auto callInstruction = llvm::CallInst::Create(irInvocableType->getIRFunctionType()->getType(), source->getValue(), argList);
        return new IRFunctionInvocationExpressionNode(node, source, callInstruction, irType, arguments, irReturnType, varArgsTypeValueArgument);
    }

    if (node->getFunction()->getTypeSignature()->isBuiltIn()) {
        auto irFunctionType = (IRFunctionType*)irType;
        auto irParameterList = irGenerator->generateIRTypes(node->getTypeSignature()->getFunctionType()->getParameterTypes(), scope, irContext);

        auto irFunctionName = node->getFunction()->getTypeSignature()->isDebug()
                ? irGenerator->getJetDebugFunctionName(node->getFunction()->getId())
                : irGenerator->getJetUtilsFunctionName(node->getFunction()->getId(), argList.size());
        auto function = irContext->getModule()->getFunction(irFunctionName);
        auto irFunction = IRInstructionNodeFactory::create(function, irGenerator->generateIrPointerType(irFunctionType));

        if (node->getTypeSignature()->getFunctionType()->isOneOfBuiltInTypeSources({
                   BI_ASSERT_TYPE_SOURCE,
                   BI_ASSERT_WITH_MESSAGE_TYPE_SOURCE,
                   BI_ASSERT_DEBUG_LAMBDA_REF_COUNT_TYPE_SOURCE,
                   BI_ASSERT_DEBUG_REF_COUNT_TYPE_SOURCE,
                   BI_ASSERT_DEBUG_STRUCT_REF_COUNT_TYPE_SOURCE,
                   BI_ASSERT_DEBUG_TUPLE_REF_COUNT_TYPE_SOURCE,
                   BI_ASSERT_DEBUG_CLASS_REF_COUNT_TYPE_SOURCE
        })) {
            auto assertMessage = irGenerator->getOrInsertGlobalVariableString(node->getId(), "(" + node->getLineColumn() + ") " + node->toSourceCode() + "\n\n", irContext);
            argList.push_back(assertMessage);
        }
        auto callInstruction = llvm::CallInst::Create(function->getFunctionType(), function, argList);
        return new IRFunctionInvocationExpressionNode(node, irFunction, callInstruction, irType, arguments, irReturnType, varArgsTypeValueArgument);
    }

    auto irFunctionType = (IRFunctionType*)irType;
    auto irFunctionId = FunctionIdGenerator::generateFor(node->getFunction()->getModuleId(), node->getFunction()->getId(), (InvocableTypeSignature*)node->getFunction()->getTypeSignature());
    auto function = irContext->getModule()->getFunction(irFunctionId);
    auto irFunction = IRInstructionNodeFactory::create(function, irGenerator->generateIrPointerType(irFunctionType));
    auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, argList);
    return new IRFunctionInvocationExpressionNode(node, irFunction, callInstruction, irType, arguments, irReturnType, varArgsTypeValueArgument);
}