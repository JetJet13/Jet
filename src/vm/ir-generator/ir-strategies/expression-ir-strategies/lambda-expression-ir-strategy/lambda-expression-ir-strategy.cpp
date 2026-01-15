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
#include "../../../../../shared/utils/logger/logger.h"

IRLambdaWithBlockExpressionNode* LambdaExpressionIRStrategy::generate(ASTLambdaExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto lambdaScope = new IRLookupTable(scope);
    auto irType = (IRLambdaType*)irGenerator->generateTypeFor(node->getTypeSignature(), lambdaScope, irContext);
    auto functionTypeNode = irGenerator->generateTypeFor(node->getTypeSignature(), lambdaScope, irContext);
    auto functionType = llvm::cast<llvm::FunctionType>(functionTypeNode->getType());
    auto irFunction = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, "", irContext->getModule());
    auto irCleanupFunction = this->generateLambdaCleanupFunction(irType, irGenerator, irContext);
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), lambdaScope, irContext, irFunction);
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);

    this->setupParameters(node->getTypeSignature(), irGenerator, lambdaScope, irFunction, functionParameterList, functionBlock, irContext);
    for (auto statement : *node->getBlock()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(statement)) {
            functionBlock->insert(irGenerator->generateFor((ASTDeclarationNode*)statement, lambdaScope, irContext));
        } else if (ASTNodeUtils::isStatementNode(statement)) {
            functionBlock->insert(irGenerator->generateFor((ASTStatementNode*)statement, lambdaScope, irContext));
        }
    }
    auto allocation = IRInstructionNodeFactory::create(irType->getLambdaVariableType());
    return new IRLambdaWithBlockExpressionNode(node, allocation, irFunction, functionParameterList, functionBlock, irType, irCleanupFunction, lambdaScope);
}

IRLambdaWithFatArrowExpressionNode* LambdaExpressionIRStrategy::generate(ASTLambdaWithFatArrowExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto lambdaScope = new IRLookupTable(scope);
    auto irType = (IRLambdaType*)irGenerator->generateTypeFor(node->getTypeSignature(), lambdaScope, irContext);
    auto functionTypeNode = irGenerator->generateTypeFor(node->getTypeSignature(), lambdaScope, irContext);
    auto functionType = llvm::cast<llvm::FunctionType>(functionTypeNode->getType());
    auto irFunction = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, "", irContext->getModule());
    auto irCleanupFunction = this->generateLambdaCleanupFunction(irType, irGenerator, irContext);
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), lambdaScope, irContext, irFunction);
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);

    this->setupParameters(node->getTypeSignature(), irGenerator, lambdaScope, irFunction, functionParameterList, functionBlock, irContext);
    auto returnExpression = irGenerator->generateFor(node->getReturnExpression()->getExpression(), lambdaScope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    auto allocation = IRInstructionNodeFactory::create(irType->getLambdaVariableType());
    return new IRLambdaWithFatArrowExpressionNode(node, allocation, irFunction, functionParameterList, functionBlock, irType, irCleanupFunction, returnExpression, lambdaScope);
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