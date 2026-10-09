// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-05-23.
//

#include "block-type-signature-strategy.h"

void BlockTypeSignatureStrategy::assign(std::shared_ptr<ASTBlockNode> blockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(blockNode->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(std::shared_ptr<ASTControlFlowBlockNode> controlFlowBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(controlFlowBlockNode->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(std::shared_ptr<ASTFunctionBlockNode> functionBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(functionBlockNode->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(std::shared_ptr<ASTTryBlockNode> tryBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(tryBlockNode->getBlock()->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(std::shared_ptr<ASTCatchBlockNode> catchBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(catchBlockNode->getBlock()->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assign(std::shared_ptr<ASTFinallyBlockNode> finallyBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    this->assignContents(finallyBlockNode->getBlock()->getContents(), context, scope, strategyMap);
}

void BlockTypeSignatureStrategy::assignContents(std::vector<std::shared_ptr<ASTNode>>* content, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    for (auto statement : *content) {
        strategyMap->assignTypeSignatureFor(statement, context, scope);
    }
}