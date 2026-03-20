//
// Created by Johny Georges on 2024-05-23.
//

#include "block-type-signature-strategy.h"

void BlockTypeSignatureStrategy::assign(ASTBlockNode* blockNode, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(blockNode->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTControlFlowBlockNode* controlFlowBlockNode, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(controlFlowBlockNode->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTFunctionBlockNode* functionBlockNode, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(functionBlockNode->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTTryBlockNode* tryBlockNode, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(tryBlockNode->getBlock()->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTCatchBlockNode* catchBlockNode, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(catchBlockNode->getBlock()->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTFinallyBlockNode* finallyBlockNode, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(finallyBlockNode->getBlock()->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assignContents(std::vector<ASTNode*>* content, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    for (auto statement : *content) {
        strategyMap->assignTypeSignatureFor(statement, context, scope);
    }
}