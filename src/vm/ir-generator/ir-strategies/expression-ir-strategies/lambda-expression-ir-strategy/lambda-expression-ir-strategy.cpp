//
// Created by Johny Georges on 2024-11-12.
//

#include "lambda-expression-ir-strategy.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../core/type-signature/pointer-type-signature/pointer-type-signature.h"

IRLambdaExpressionNode* LambdaExpressionIRStrategy::generate(ASTLambdaExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto lambdaScope = new IRLookupTable();
    lambdaScope->inheritGlobalScope(scope);
    auto functionTypeNode = irGenerator->generateTypeFor(node->getTypeSignature());
    auto functionType = llvm::cast<llvm::FunctionType>(functionTypeNode->getType());
    auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    auto irFunction = llvm::Function::Create(functionType, linkage, node->getId(), irModule->getModule());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), scope, irModule, irFunction);
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);

    this->setupParameters(node->getTypeSignature(), irGenerator, lambdaScope, irFunction, functionParameterList, functionBlock, irModule);

    for (auto statement : *node->getBlock()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(statement)) {
            irGenerator->getInjector()->inject(functionBlock, irGenerator->generateFor((ASTDeclarationNode*)statement, lambdaScope, irModule), irModule);
        } else if (ASTNodeUtils::isStatementNode(statement)) {
            irGenerator->getInjector()->inject(functionBlock, irGenerator->generateFor((ASTStatementNode*)statement, lambdaScope, irModule), irModule);
        }
    }

    if (!node->getReturnType()) {
        irGenerator->getInjector()->injectVoidReturnType(functionBlock);
    }
    return new IRLambdaExpressionNode(node, irFunction, functionParameterList, functionBlock, new IRLambdaType(irFunction->getFunctionType()));
}

IRLambdaWithFatArrowExpressionNode* LambdaExpressionIRStrategy::generate(ASTLambdaWithFatArrowExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto lambdaScope = new IRLookupTable();
    lambdaScope->inheritGlobalScope(scope);
    auto functionTypeNode = irGenerator->generateTypeFor(node->getTypeSignature());
    auto functionType = llvm::cast<llvm::FunctionType>(functionTypeNode->getType());
    auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    auto irFunction = llvm::Function::Create(functionType, linkage, node->getId(), irModule->getModule());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), scope, irModule, irFunction);
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);

    this->setupParameters(node->getTypeSignature(), irGenerator, lambdaScope, irFunction, functionParameterList, functionBlock, irModule);

    auto returnExpression = irGenerator->generateFor(node->getReturnExpression()->getExpression(), lambdaScope, irModule, IR_OPERAND_OP);
    auto irReturnExpressionValue = irGenerator->getInjector()->inject(functionBlock, returnExpression, IR_OPERAND_OP, irModule);
    functionBlock->getBuilder()->get()->CreateRet(irReturnExpressionValue);
    return new IRLambdaWithFatArrowExpressionNode(node, irFunction, functionParameterList, functionBlock, new IRLambdaType(irFunction->getFunctionType()));
}

void LambdaExpressionIRStrategy::setupParameters(LambdaExpressionTypeSignature* typeSignature, IRGenerator* irGenerator, IRLookupTable* scope, llvm::Function* irFunction, IRFunctionParameterListNode* functionParameterList, IRBlockNode* functionBlock, IRModuleNode* irModule) {
    if (typeSignature->isScopeParameterNecessary()) {
        auto lambdaScopeParameterType = irGenerator->generateParameterType(typeSignature->getScopeParameter());
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
                        DataAlignmentGenerator::generate(irParamType)
                ), irGenerator->generateIrPointerType(irParamType));
        scope->insert(formalParameter->getParameterType()->getName(), functionParameterAllocation);
        irGenerator->getInjector()->inject(functionBlock, new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation), irModule);
        if (formalParameter->getParameterType()->getName() == typeSignature->getScopeParameter()->getName()) {
            auto scopeParameterIrType = (IRStructType*)formalParameter->getParameterType()->getIRType();
            auto scopeParameterTypeSignature = (StructTypeSignature*)typeSignature->getScopeParameter()->getTypeSignature();
            auto zeroIndex = irGenerator->generateIntConstant(0);
            for (const auto& keyValue : scopeParameterTypeSignature->getKeyValuePairs()->getKeyValues()) {
                auto underlyingType = ((PointerTypeSignature*)keyValue.second)->getUnderlyingType();
                auto underlyingIrType = irGenerator->generateTypeFor(underlyingType);
                auto index = irGenerator->generateIntConstant(scopeParameterIrType->getIndexForKey(keyValue.first));
                auto irType = scopeParameterIrType->getIRTypeForKey(keyValue.first);
                auto pointerToValue = functionBlock->getBuilder()->get()->CreateInBoundsGEP(scopeParameterIrType->getType(), functionParameterAllocation->getValue(), { zeroIndex, index });
                auto allocation = functionBlock->getBuilder()->get()->CreateAlloca(irType->getType(), nullptr, "scope." + keyValue.first);
                functionBlock->getBuilder()->get()->CreateStore(
                        functionBlock->getBuilder()->get()->CreateLoad(irType->getType(), pointerToValue),
                        allocation
                );
                scope->insert(
                        keyValue.first,
                        IRInstructionNodeFactory::create(allocation, irGenerator->generateIrPointerType(underlyingIrType))
                );
            }
        }
    }
}