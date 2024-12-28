//
// Created by Johny Georges on 2024-05-23.
//

#include "block-type-signature-strategy.h"

void BlockTypeSignatureStrategy::assign(ASTBlockNode* blockNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(blockNode->getContents(), scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTControlFlowBlockNode* controlFlowBlockNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(controlFlowBlockNode->getContents(), scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTFunctionBlockNode* functionBlockNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(functionBlockNode->getContents(), scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTTryBlockNode* tryBlockNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(tryBlockNode->getBlock()->getContents(), scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTCatchBlockNode* catchBlockNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(catchBlockNode->getBlock()->getContents(), scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTFinallyBlockNode* finallyBlockNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(finallyBlockNode->getBlock()->getContents(), scope, strategyMap);
}

void BlockTypeSignatureStrategy::assignContents(std::vector<ASTNode*>* content, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    for (auto statement : *content) {
        strategyMap->assignTypeSignatureFor(statement, scope);
    }
}