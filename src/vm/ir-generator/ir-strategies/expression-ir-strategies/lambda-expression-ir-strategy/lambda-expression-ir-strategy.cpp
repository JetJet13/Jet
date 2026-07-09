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

std::shared_ptr<IRLambdaWithBlockExpressionNode> LambdaExpressionIRStrategy::generate(std::shared_ptr<ASTLambdaExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto lambdaScope = std::make_shared<IRLookupTable>(scope);
    auto irType = std::dynamic_pointer_cast<IRLambdaType>(irGenerator->generateTypeFor(node->getTypeSignature(), lambdaScope, irContext));
    auto functionType = irType->getFunctionType();
    auto irFunction = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, "", irContext->getModule());
    auto irCleanupFunction = this->generateLambdaCleanupFunction(irType, irGenerator, irContext);
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), lambdaScope, irContext, irFunction);
    auto lambdaBlock = irGenerator->generateFunctionBlock(irFunction, lambdaScope);
    auto lambdaIrContext = irGenerator->generateContext(lambdaBlock, irContext->getIRModule());

    this->setupParameters(node->getLambdaTypeSignature(), irGenerator, lambdaBlock->getScope(), irFunction, functionParameterList, lambdaBlock, lambdaIrContext);
    for (auto statement : *node->getBlock()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(statement)) {
            lambdaBlock->insert(irGenerator->generateFor(std::dynamic_pointer_cast<ASTDeclarationNode>(statement), lambdaBlock->getScope(), lambdaIrContext));
        } else if (ASTNodeUtils::isStatementNode(statement)) {
            lambdaBlock->insert(irGenerator->generateFor(std::dynamic_pointer_cast<ASTStatementNode>(statement), lambdaBlock->getScope(), lambdaIrContext));
        } else if (statement->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
            lambdaBlock->insert(irGenerator->generateFor(std::dynamic_pointer_cast<ASTFunctionReturnExpressionNode>(statement), lambdaBlock->getScope(), lambdaIrContext));
        }
    }
    auto allocation = IRInstructionNodeFactory::create(irType->getLambdaVariableType());
    return std::make_shared<IRLambdaWithBlockExpressionNode>(node, allocation, irFunction, functionParameterList, lambdaBlock, irType, irCleanupFunction);
}

std::shared_ptr<IRLambdaWithFatArrowExpressionNode> LambdaExpressionIRStrategy::generate(std::shared_ptr<ASTLambdaWithFatArrowExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto lambdaScope = std::make_shared<IRLookupTable>(scope);
    auto irType = std::dynamic_pointer_cast<IRLambdaType>(irGenerator->generateTypeFor(node->getLambdaTypeSignature(), lambdaScope, irContext));
    auto functionType = irType->getFunctionType();
    auto irFunction = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, "", irContext->getModule());
    auto irCleanupFunction = this->generateLambdaCleanupFunction(irType, irGenerator, irContext);
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), lambdaScope, irContext, irFunction);
    auto lambdaBlock = irGenerator->generateFunctionBlock(irFunction, lambdaScope);
    auto lambdaIrContext = irGenerator->generateContext(lambdaBlock, irContext->getIRModule());

    this->setupParameters(node->getLambdaTypeSignature(), irGenerator, lambdaBlock->getScope(), irFunction, functionParameterList, lambdaBlock, lambdaIrContext);
    auto returnExpression = irGenerator->generateFor(node->getReturnExpression()->getExpression(), lambdaBlock->getScope(), lambdaIrContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    returnExpression->markAsReturned();
    auto allocation = IRInstructionNodeFactory::create(irType->getLambdaVariableType());
    return std::make_shared<IRLambdaWithFatArrowExpressionNode>(node, allocation, irFunction, functionParameterList, lambdaBlock, irType, irCleanupFunction, returnExpression);
}

void LambdaExpressionIRStrategy::setupParameters(std::shared_ptr<LambdaExpressionTypeSignature> typeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, llvm::Function* irFunction, std::shared_ptr<IRFunctionParameterListNode> functionParameterList, std::shared_ptr<IRBlockNode> functionBlock, std::shared_ptr<IRContext> irContext) {
    for (unsigned long i = 0; i < functionParameterList->getParameters()->size(); ++i) {
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto functionParameterAllocation = formalParameter->getAllocation();
        functionBlock->insert(
                std::make_shared<IRFunctionParameterDeclarationNode>(irFunction->getArg(i), functionParameterAllocation, formalParameter->getArc())
        );
    }

    auto lambdaScopeParameterType = irGenerator->generateParameterType(typeSignature->getScopeParameter(), scope, irContext);
    auto argument = new llvm::Argument(lambdaScopeParameterType->getType(), lambdaScopeParameterType->getName(), irFunction, irFunction->arg_size() - 1);
    auto scopeParameter = std::make_shared<IRFunctionParameterNode>(argument, lambdaScopeParameterType, irGenerator->generateFunctionParameterAllocation(lambdaScopeParameterType->getIRType()));
    functionParameterList->addLambdaScopeParameter(scopeParameter);

    if (typeSignature->isScopeParameterNecessary()) {
        auto scopeParameterIrType = std::dynamic_pointer_cast<IRStructType>(scopeParameter->getParameterType()->getIRType());
        auto scopeParameterAllocation = scopeParameter->getAllocation();
        auto loadedScopeParameterArgument = irGenerator->generateLoadInstruction(irFunction->getArg(argument->getArgNo()), lambdaScopeParameterType->getIRType());
        auto storedScopeParameterArgument = irGenerator->generateStoreInstruction(loadedScopeParameterArgument, scopeParameterAllocation->getValue(), lambdaScopeParameterType->getIRType());
        scopeParameterAllocation->insertDescendentValue(loadedScopeParameterArgument);
        scopeParameterAllocation->insertDescendentValue(storedScopeParameterArgument);
        for (unsigned long index = 0; index < scopeParameterIrType->size(); ++index) {
            auto key = scopeParameterIrType->getKeyForIndex(index);
            auto irType = std::dynamic_pointer_cast<IRCapturedVariableType>(scopeParameterIrType->getIRTypeForKey(key));
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

llvm::Function* LambdaExpressionIRStrategy::generateLambdaCleanupFunction(std::shared_ptr<IRLambdaType> irLambdaType, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext) {
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
            auto typeValue = irGenerator->getInjector()->inject(functionBlock, irType, irContext->getIRModule());
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