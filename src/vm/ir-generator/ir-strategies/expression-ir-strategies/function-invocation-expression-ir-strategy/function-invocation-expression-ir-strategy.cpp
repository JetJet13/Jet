//
// Created by Johny Georges on 2024-11-08.
//

#include "function-invocation-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../../shared/utils/function-id-generator/function-id-generator.h"

std::shared_ptr<IRExpressionNode> FunctionInvocationExpressionIRStrategy::generate(std::shared_ptr<ASTFunctionInvocationExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto arguments = std::vector<std::shared_ptr<IRFunctionArgumentNode>>();
    for (unsigned long i = 0; i < node->getArguments()->numArguments(); ++i) {
        arguments.push_back(
                irGenerator->generateFor(
                        node->getArguments()->getArguments()->at(i),
                        i,
                        scope,
                        irContext,
                        std::make_shared<IROperation>(IR_FUNCTION_ARGUMENT_OP),
                        node->getInvocationTypeSignature()->getFunctionType()
                )
        );
    }
    auto argList = irGenerator->generateArgumentPlaceholderListForFunction(node->getInvocationTypeSignature()->getFunctionType(), &arguments, scope, irContext);

    std::optional<std::shared_ptr<IRInstructionNode>> varArgsTypeValueArgument = {};
    if (node->getInvocationTypeSignature()->getFunctionType()->hasVariableLengthParameters()) {
        auto startIndex = node->getInvocationTypeSignature()->getFunctionType()->getVariableLengthParametersStartIndex();
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
    auto irReturnType = irGenerator->generateTypeFor(node->getInvocationTypeSignature()->getReturnType(), scope, irContext);

    if (irType->isInvocableType()) {
        auto irInvocableType = std::dynamic_pointer_cast<IRInvocableType>(irType);
        auto source = scope->findAcrossScopes(node->getFunction()->getModuleId(), node->getFunction()->getId()).value();
        auto callInstruction = llvm::CallInst::Create(irInvocableType->getIRFunctionType()->getType(), source->getValue(), argList);
        return std::make_shared<IRFunctionInvocationExpressionNode>(node, source, callInstruction, irType, arguments, irReturnType, varArgsTypeValueArgument);
    }

    if (node->getFunction()->getTypeSignature()->isBuiltIn()) {
        auto irFunctionType = std::dynamic_pointer_cast<IRFunctionType>(irType);
        auto irParameterList = irGenerator->generateIRTypes(node->getInvocationTypeSignature()->getFunctionType()->getParameterTypes(), scope, irContext);

        auto irFunctionName = node->getFunction()->getTypeSignature()->isDebug()
                ? irGenerator->getJetDebugFunctionName(node->getFunction()->getId())
                : irGenerator->getJetUtilsFunctionName(node->getFunction()->getId(), argList.size());
        auto function = irContext->getModule()->getFunction(irFunctionName);
        auto irFunction = IRInstructionNodeFactory::create(function, irGenerator->generateIrPointerType(irFunctionType));

        if (node->getInvocationTypeSignature()->getFunctionType()->isOneOfBuiltInTypeSources({
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
        return std::make_shared<IRFunctionInvocationExpressionNode>(node, irFunction, callInstruction, irType, arguments, irReturnType, varArgsTypeValueArgument);
    }

    auto irFunctionType = std::dynamic_pointer_cast<IRFunctionType>(irType);
    auto irFunctionId = FunctionIdGenerator::generateFor(node->getFunction()->getModuleId(), node->getFunction()->getId(), std::dynamic_pointer_cast<InvocableTypeSignature>(node->getFunction()->getTypeSignature()));
    auto function = irContext->getModule()->getFunction(irFunctionId);
    auto irFunction = IRInstructionNodeFactory::create(function, irGenerator->generateIrPointerType(irFunctionType));
    auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, argList);
    return std::make_shared<IRFunctionInvocationExpressionNode>(node, irFunction, callInstruction, irType, arguments, irReturnType, varArgsTypeValueArgument);
}