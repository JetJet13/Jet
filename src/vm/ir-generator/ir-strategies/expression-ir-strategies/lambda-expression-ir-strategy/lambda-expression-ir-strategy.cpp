//
// Created by Johny Georges on 2024-11-12.
//

#include "lambda-expression-ir-strategy.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../ir-injector/ir-injector-strategies/ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"
#include "../../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

IRLambdaExpressionNode* LambdaExpressionIRStrategy::generate(ASTLambdaExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto lambdaScope = new IRLookupTable(scope);
    auto irType = (IRLambdaType*)irGenerator->generateTypeFor(node->getTypeSignature(), lambdaScope, irContext);
    auto functionTypeNode = irGenerator->generateTypeFor(node->getTypeSignature(), lambdaScope, irContext);
    auto functionType = llvm::cast<llvm::FunctionType>(functionTypeNode->getType());
    auto irFunction = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, "", irContext->getModule());
    auto irCleanupFunction = this->generateLambdaCleanupFunction(irType, irGenerator, irContext);
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), scope, irContext, irFunction);
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);

    this->setupParameters(node->getTypeSignature(), irGenerator, lambdaScope, irFunction, functionParameterList, functionBlock, irContext);
    for (auto statement : *node->getBlock()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(statement)) {
            irGenerator->getInjector()->inject(functionBlock, irGenerator->generateFor((ASTDeclarationNode*)statement, lambdaScope, irContext), irContext->getIRModule(), lambdaScope);
        } else if (ASTNodeUtils::isStatementNode(statement)) {
            irGenerator->getInjector()->inject(functionBlock, irGenerator->generateFor((ASTStatementNode*)statement, lambdaScope, irContext), irContext->getIRModule(), lambdaScope);
        }
    }

    if (functionType->getReturnType()->isVoidTy()) {
        irGenerator->getInjector()->injectVoidReturnType(functionBlock);
    }

    FreeIRInjectorHelper::freeFunctionBlockNodes(functionBlock, irGenerator->getInjector(), irContext->getIRModule(),
                                                 scope);
    FreeIRInjectorHelper::freeFunctionParameters(functionBlock, functionParameterList, irGenerator->getInjector(), irContext->getIRModule(), lambdaScope);
    DebugIRInjectorHelper::injectFunctionEnterLog(functionBlock, irFunction->getName().str(), irGenerator->getInjector(), irContext->getIRModule());
    DebugIRInjectorHelper::injectFunctionExitLog(functionBlock, irFunction->getName().str(), irGenerator->getInjector(), irContext->getIRModule());
    return new IRLambdaExpressionNode(node, irFunction, functionParameterList, functionBlock, irType, irCleanupFunction);
}

IRLambdaWithFatArrowExpressionNode* LambdaExpressionIRStrategy::generate(ASTLambdaWithFatArrowExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto lambdaScope = new IRLookupTable(scope);
    auto irType = (IRLambdaType*)irGenerator->generateTypeFor(node->getTypeSignature(), lambdaScope, irContext);
    auto functionTypeNode = irGenerator->generateTypeFor(node->getTypeSignature(), lambdaScope, irContext);
    auto functionType = llvm::cast<llvm::FunctionType>(functionTypeNode->getType());
    auto irFunction = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, "", irContext->getModule());
    auto irCleanupFunction = this->generateLambdaCleanupFunction(irType, irGenerator, irContext);
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), scope, irContext, irFunction);
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);

    this->setupParameters(node->getTypeSignature(), irGenerator, lambdaScope, irFunction, functionParameterList, functionBlock, irContext);
    auto returnExpression = irGenerator->generateFor(node->getReturnExpression()->getExpression(), lambdaScope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    auto irReturnExpressionValue = irGenerator->getInjector()->inject(functionBlock, returnExpression, new IROperation(IR_OPERAND_VALUE_OP), irContext->getIRModule(), lambdaScope);
    functionBlock->getBuilder()->get()->CreateRet(irReturnExpressionValue);

    FreeIRInjectorHelper::freeFunctionParameters(functionBlock, functionParameterList, irGenerator->getInjector(), irContext->getIRModule(), lambdaScope);
    DebugIRInjectorHelper::injectFunctionEnterLog(functionBlock, irFunction->getName().str(), irGenerator->getInjector(), irContext->getIRModule());
    DebugIRInjectorHelper::injectFunctionExitLog(functionBlock, irFunction->getName().str(), irGenerator->getInjector(), irContext->getIRModule());
    return new IRLambdaWithFatArrowExpressionNode(node, irFunction, functionParameterList, functionBlock, irType, irCleanupFunction);
}

void LambdaExpressionIRStrategy::setupParameters(LambdaExpressionTypeSignature* typeSignature, IRGenerator* irGenerator, IRLookupTable* scope, llvm::Function* irFunction, IRFunctionParameterListNode* functionParameterList, IRBlockNode* functionBlock, IRContext* irContext) {
    if (typeSignature->isScopeParameterNecessary()) {
        auto lambdaScopeParameterType = irGenerator->generateParameterType(typeSignature->getScopeParameter(), scope, irContext);
        auto argument = new llvm::Argument(lambdaScopeParameterType->getType(), lambdaScopeParameterType->getName(), irFunction, 0);
        functionParameterList->addScopeParameter(new IRFunctionParameterNode(argument, lambdaScopeParameterType));
    }
    auto functionType = irFunction->getFunctionType();
    for (int i = 0; i < functionType->getNumParams(); ++i) {
        auto parameter = functionType->params()[i];
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto irParamType = formalParameter->getParameterType()->getIRType();
        auto functionParameterAllocation = new IRInstructionNode(
                new llvm::AllocaInst(
                        parameter,
                        AddressSpaceGenerator::generate(irParamType),
                        nullptr,
                        irParamType->getAlignment()
                ), irGenerator->generateIrPointerType(irParamType));
        scope->insert(formalParameter->getParameterType()->getName(), functionParameterAllocation);
        irGenerator->getInjector()->inject(functionBlock, new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation), irContext->getIRModule(), scope);
        if (formalParameter->getParameterType()->getName() == typeSignature->getScopeParameter()->getName()) {
            auto scopeParameterIrType = (IRStructType*)formalParameter->getParameterType()->getIRType();
            auto pointerToScopeParameterType = InstructionIRInjectorHelper::injectLoad(functionParameterAllocation->getAllocatedType(), functionParameterAllocation->getValue(), functionBlock);
            for (int index = 0; index < scopeParameterIrType->size(); ++index) {
                auto key = scopeParameterIrType->getKeyForIndex(index);
                auto irType = (IRCapturedVariableType*)scopeParameterIrType->getIRTypeForKey(key);
                auto pointerToCapturedVariableValue = functionBlock->getBuilder()->get()->CreateStructGEP(scopeParameterIrType->getType(), pointerToScopeParameterType, index);
                auto loadedCapturedVariableValue = InstructionIRInjectorHelper::injectLoad(irType->getType(), pointerToCapturedVariableValue, functionBlock, irType);
                auto pointerToValue = functionBlock->getBuilder()->get()->CreateExtractValue(loadedCapturedVariableValue, irType->getVariableIndex());
                auto pointerToCaptureCounterValue = functionBlock->getBuilder()->get()->CreateExtractValue(loadedCapturedVariableValue, irType->getCaptureCounterIndex());
                scope->insert(
                    key,
                    IRInstructionNodeFactory::create(pointerToValue, irGenerator->generateIrPointerType(irType->getVariableIRType()))
                );
                scope->insertArc(key, IRInstructionNodeFactory::create(pointerToCaptureCounterValue,
                                                                       irGenerator->generateIrPointerType(
                                                                               irType->getCaptureCounterIRType())));
            }
        }
    }
}

llvm::Function* LambdaExpressionIRStrategy::generateLambdaCleanupFunction(IRLambdaType* irLambdaType, IRGenerator* irGenerator, IRContext* irContext) {
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType->getType(), { pointerType }, false);
    auto lambdaCleanupFunctionName = "lambda.clean.up";
    auto irFunction = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, lambdaCleanupFunctionName, irContext->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);
    if (irLambdaType->getLambdaScopeType()) {
        auto lambdaScopeArgumentType = irLambdaType->getLambdaScopeType().value();
        for (int i = 0; i < lambdaScopeArgumentType->size(); ++i) {
            auto key = lambdaScopeArgumentType->getKeyForIndex(i);
            auto irType = lambdaScopeArgumentType->getIRTypeForKey(key);
            auto pointerToCapturedVariable = functionBlock->getBuilder()->get()->CreateStructGEP(lambdaScopeArgumentType->getType(), irFunction->getArg(0), i);
            auto typeValue = irGenerator->getInjector()->inject(functionBlock, irType);
            auto capturedVariableTypeValue = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), typeValue, functionBlock);
            functionBlock->getBuilder()->get()->CreateCall(
                irContext->getIRModule()->getFreeCapturedVariableFunction(),
                { pointerToCapturedVariable, capturedVariableTypeValue }
            );
        }
    }
    functionBlock->addVoidReturn();
    return irFunction;
}