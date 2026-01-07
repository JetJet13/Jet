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
    auto irFunctionContext = irContext->clone(functionBlock);
    for (int i = 0; i < functionType->getNumParams(); ++i) {
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto functionParameterAllocation = formalParameter->getAllocation();
//        functionScope->insert(formalParameter->getParameterType()->getName(), functionParameterAllocation);
//        if (formalParameter->getArc()) {
//            functionScope->insertArc(formalParameter->getParameterType()->getName(), formalParameter->getArc().value());
//        }
        functionBlock->insert(new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation, formalParameter->getArc()));
    }

    for (auto statement : *node->getBlock()->getContents()) {
        functionBlock->insert(irGenerator->generateFor(statement, functionScope, irFunctionContext));
    }
    return new IRFunctionDeclarationNode(node, irFunction, functionParameterList, functionBlock, functionScope);
}