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

IRLambdaWithBlockExpressionNode* LambdaExpressionIRStrategy::generate(ASTLambdaExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto lambdaScope = new IRLookupTable(scope);
    auto irType = (IRLambdaType*)irGenerator->generateTypeFor(node->getTypeSignature(), lambdaScope, irContext);
    auto functionType = irType->getFunctionType();
    auto irFunction = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, "", irContext->getModule());
    auto irCleanupFunction = this->generateLambdaCleanupFunction(irType, irGenerator, irContext);
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), lambdaScope, irContext, irFunction);
    auto lambdaBlock = irGenerator->generateFunctionBlock(irFunction, lambdaScope);
    auto lambdaIrContext = irGenerator->generateContext(lambdaBlock, irContext->getIRModule());

    this->setupParameters(node->getTypeSignature(), irGenerator, lambdaBlock->getScope(), irFunction, functionParameterList, lambdaBlock, lambdaIrContext);
    for (auto statement : *node->getBlock()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(statement)) {
            lambdaBlock->insert(irGenerator->generateFor((ASTDeclarationNode*)statement, lambdaBlock->getScope(), lambdaIrContext));
        } else if (ASTNodeUtils::isStatementNode(statement)) {
            lambdaBlock->insert(irGenerator->generateFor((ASTStatementNode*)statement, lambdaBlock->getScope(), lambdaIrContext));
        }
    }
    auto allocation = IRInstructionNodeFactory::create(irType->getLambdaVariableType());
    return new IRLambdaWithBlockExpressionNode(node, allocation, irFunction, functionParameterList, lambdaBlock, irType, irCleanupFunction);
}

IRLambdaWithFatArrowExpressionNode* LambdaExpressionIRStrategy::generate(ASTLambdaWithFatArrowExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto lambdaScope = new IRLookupTable(scope);
    auto irType = (IRLambdaType*)irGenerator->generateTypeFor(node->getTypeSignature(), lambdaScope, irContext);
    auto functionType = irType->getFunctionType();
    auto irFunction = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, "", irContext->getModule());
    auto irCleanupFunction = this->generateLambdaCleanupFunction(irType, irGenerator, irContext);
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), lambdaScope, irContext, irFunction);
    auto lambdaBlock = irGenerator->generateFunctionBlock(irFunction, lambdaScope);
    auto lambdaIrContext = irGenerator->generateContext(lambdaBlock, irContext->getIRModule());

    this->setupParameters(node->getTypeSignature(), irGenerator, lambdaBlock->getScope(), irFunction, functionParameterList, lambdaBlock, lambdaIrContext);
    auto returnExpression = irGenerator->generateFor(node->getReturnExpression()->getExpression(), lambdaBlock->getScope(), lambdaIrContext, new IROperation(IR_OPERAND_VALUE_OP));
    auto allocation = IRInstructionNodeFactory::create(irType->getLambdaVariableType());
    return new IRLambdaWithFatArrowExpressionNode(node, allocation, irFunction, functionParameterList, lambdaBlock, irType, irCleanupFunction, returnExpression);
}

void LambdaExpressionIRStrategy::setupParameters(LambdaExpressionTypeSignature* typeSignature, IRGenerator* irGenerator, IRLookupTable* scope, llvm::Function* irFunction, IRFunctionParameterListNode* functionParameterList, IRBlockNode* functionBlock, IRContext* irContext) {
    for (unsigned long i = 0; i < functionParameterList->getParameters()->size(); ++i) {
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto functionParameterAllocation = formalParameter->getAllocation();
        functionBlock->insert(
                new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation, formalParameter->getArc())
        );
    }

    if (typeSignature->isScopeParameterNecessary()) {
        auto lambdaScopeParameterType = irGenerator->generateParameterType(typeSignature->getScopeParameter(), scope, irContext);
        auto argument = new llvm::Argument(lambdaScopeParameterType->getType(), lambdaScopeParameterType->getName(), irFunction, irFunction->arg_size() - 1);
        auto scopeParameter = new IRFunctionParameterNode(argument, lambdaScopeParameterType, irGenerator->generateFunctionParameterAllocation(lambdaScopeParameterType->getIRType()));
        functionParameterList->addLambdaScopeParameter(scopeParameter);
        auto scopeParameterIrType = (IRStructType*)scopeParameter->getParameterType()->getIRType();
        auto scopeParameterAllocation = scopeParameter->getAllocation();
        auto loadedScopeParameterArgument = irGenerator->generateLoadInstruction(irFunction->getArg(argument->getArgNo()), lambdaScopeParameterType->getIRType());
        auto storedScopeParameterArgument = irGenerator->generateStoreInstruction(loadedScopeParameterArgument, scopeParameterAllocation->getValue(), lambdaScopeParameterType->getIRType());
        scopeParameterAllocation->insertDescendentValue(loadedScopeParameterArgument);
        scopeParameterAllocation->insertDescendentValue(storedScopeParameterArgument);
        for (unsigned long index = 0; index < scopeParameterIrType->size(); ++index) {
            auto key = scopeParameterIrType->getKeyForIndex(index);
            auto irType = (IRCapturedVariableType*)scopeParameterIrType->getIRTypeForKey(key);
            auto pointerToCapturedVariableValue = irGenerator->generateGEP(scopeParameterIrType, scopeParameterAllocation->getValue(), index);
            auto loadedCapturedVariableValue = irGenerator->generateLoadInstruction(pointerToCapturedVariableValue, irType);
            auto pointerToValue = irGenerator->generateExtractValue(loadedCapturedVariableValue, irType->getVariableIndex());
            auto pointerToCaptureCounterValue = irGenerator->generateExtractValue(loadedCapturedVariableValue, irType->getCaptureCounterIndex());
            scopeParameterAllocation->insertDescendentValue(pointerToCapturedVariableValue);
            scopeParameterAllocation->insertDescendentValue(loadedCapturedVariableValue);
            scopeParameterAllocation->insertDescendentValue(pointerToValue);
            scopeParameterAllocation->insertDescendentValue(pointerToCaptureCounterValue);
            scope->insert(key, IRInstructionNodeFactory::create(pointerToValue, IRPointerType::create(irType->getVariableIRType())));
            scope->insertArc(key, IRInstructionNodeFactory::create(pointerToCaptureCounterValue, IRPointerType::create(irType->getCaptureCounterIRType())));
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
        for (unsigned long i = 0; i < lambdaScopeArgumentType->size(); ++i) {
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