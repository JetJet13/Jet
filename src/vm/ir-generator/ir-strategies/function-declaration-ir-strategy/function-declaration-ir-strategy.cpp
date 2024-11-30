//
// Created by Johny Georges on 2024-07-08.
//

#include "function-declaration-ir-strategy.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../core/ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "../../../utils/address-space-generator/address-space-generator.h"

IRFunctionDeclarationNode* FunctionDeclarationIRStrategy::generate(ASTFunctionDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto functionScope = new IRLookupTable();
    functionScope->inheritGlobalScope(scope);
    auto functionTypeNode = irGenerator->generateTypeFor(node->getTypeSignature());
    auto functionType = llvm::cast<llvm::FunctionType>(functionTypeNode->getType());
    auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    auto irFunction = llvm::Function::Create(functionType, linkage, node->getId(), irModule->getModule());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), functionScope, irModule, irFunction);
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);

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

        functionScope->insert(formalParameter->getParameterType()->getName(), functionParameterAllocation);
        irGenerator->getInjector()->inject(functionBlock, new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation), irModule, functionScope);

        if (functionParameterAllocation->getIRType()->getSourceType()->isFunctionParameterType()) {
            auto allocation = functionParameterAllocation->getValue();
            auto irFunctionParameterType = (IRFunctionParameterType*)irParamType;
            auto zeroIndex = irGenerator->generateIntConstant(0);
            auto functionIndex = irGenerator->generateIntConstant(irFunctionParameterType->getFunctionIndex());
            auto pointerToFunctionPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(irFunctionParameterType->getType(), allocation, { zeroIndex, functionIndex });
            auto loadedFunctionPointer = functionBlock->getBuilder()->get()->CreateLoad(irFunctionParameterType->getIRFunctionPointer()->getType(), pointerToFunctionPointer, irFunctionParameterType->getFunctionParameterName(formalParameter->getParameterType()->getName()));
            functionScope->insert(irFunctionParameterType->getFunctionParameterName(formalParameter->getParameterType()->getName()), new IRLoadInstructionNode(loadedFunctionPointer, functionParameterAllocation));

            auto functionScopeArgumentIndex = functionBlock->getBuilder()->get()->getInt32(irFunctionParameterType->getFunctionScopeArgumentIndex());
            auto pointerToFunctionScopeArgumentPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(irFunctionParameterType->getType(), allocation, { zeroIndex, functionScopeArgumentIndex });
            auto loadedFunctionScopeArgumentPointer = functionBlock->getBuilder()->get()->CreateLoad(irFunctionParameterType->getIRFunctionPointer()->getType(), pointerToFunctionScopeArgumentPointer, irFunctionParameterType->getFunctionScopeArgumentParameterName(formalParameter->getParameterType()->getName()));
            functionScope->insert(irFunctionParameterType->getFunctionScopeArgumentParameterName(formalParameter->getParameterType()->getName()), new IRLoadInstructionNode(loadedFunctionScopeArgumentPointer, functionParameterAllocation));
        }
    }

    for (auto statement : *node->getBlock()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(statement)) {
            irGenerator->getInjector()->inject(functionBlock, irGenerator->generateFor((ASTDeclarationNode*)statement, functionScope, irModule), irModule, functionScope);
        } else if (ASTNodeUtils::isStatementNode(statement)) {
            irGenerator->getInjector()->inject(functionBlock, irGenerator->generateFor((ASTStatementNode*)statement, functionScope, irModule), irModule, functionScope);
        }
    }
    return new IRFunctionDeclarationNode(node, irFunction, functionParameterList, functionBlock);
}