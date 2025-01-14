//
// Created by Johny Georges on 2024-07-08.
//

#include "function-declaration-ir-strategy.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../utils/address-space-generator/address-space-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"

IRFunctionDeclarationNode* FunctionDeclarationIRStrategy::generate(ASTFunctionDeclarationNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto functionScope = new IRLookupTable();
    functionScope->inherit(scope);
    auto functionTypeNode = irGenerator->generateTypeFor(node->getTypeSignature(), functionScope, irContext);
    auto functionType = llvm::cast<llvm::FunctionType>(functionTypeNode->getType());

    auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    auto irFunction = llvm::Function::Create(functionType, linkage, node->getId(), irContext->getModule());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), functionScope, irContext, irFunction);
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
        functionBlock->insert(new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation));
    }

    for (auto statement : *node->getBlock()->getContents()) {
        functionBlock->insert(irGenerator->generateFor(statement, functionScope, irContext));
    }
    return new IRFunctionDeclarationNode(node, irFunction, functionParameterList, functionBlock, functionScope);
}