//
// Created by Johny Georges on 2024-05-23.
//

#include "block-type-signature-strategy.h"

void BlockTypeSignatureStrategy::assign(ASTBlockNode* blockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(blockNode->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTControlFlowBlockNode* controlFlowBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(controlFlowBlockNode->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTFunctionBlockNode* functionBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(functionBlockNode->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTTryBlockNode* tryBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(tryBlockNode->getBlock()->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTCatchBlockNode* catchBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(catchBlockNode->getBlock()->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(ASTFinallyBlockNode* finallyBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(finallyBlockNode->getBlock()->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assignContents(std::vector<ASTNode*>* content, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    for (auto statement : *content) {
        strategyMap->assignTypeSignatureFor(statement, context, scope);
    }
}