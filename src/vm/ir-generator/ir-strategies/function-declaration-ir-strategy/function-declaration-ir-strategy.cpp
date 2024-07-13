//
// Created by Johny Georges on 2024-07-08.
//

#include "function-declaration-ir-strategy.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../core/ast/ast-nodes/ast-node-utils/ast-node-utils.h"

IRFunctionDeclarationNode* FunctionDeclarationIRStrategy::generate(ASTFunctionDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto functionType = llvm::cast<llvm::FunctionType>(irGenerator->generateTypeFor(node->getTypeSignature())->getType());
    auto functionBlock = irGenerator->generateBasicBlock();
    for (auto statement : *node->getBlock()->getContents()) {
        if (ASTNodeUtils::isTypeDeclarationNode(statement)) {
            functionBlock->insert(
                    irGenerator->generateFor((ASTDeclarationNode*)statement, scope, irModule)
            );
        } else if (ASTNodeUtils::isStatementNode(statement)) {
            functionBlock->insert(
                    irGenerator->generateFor((ASTStatementNode*)statement, scope, irModule)
            );
        }
    }
    auto irFunction = llvm::Function::Create(functionType, llvm::GlobalValue::PrivateLinkage, node->getId(), irModule->getModule());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), scope, irModule, irFunction);
    return new IRFunctionDeclarationNode(node, irFunction, functionParameterList, functionBlock);
}