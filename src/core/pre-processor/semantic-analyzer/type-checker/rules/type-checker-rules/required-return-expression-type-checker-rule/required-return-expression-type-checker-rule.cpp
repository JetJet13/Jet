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
// Created by Johny Georges on 2024-05-25.
//

#include "required-return-expression-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../types/type-checker-error-message-table.h"

void RequiredReturnExpressionTypeCheckerRule::enforce(std::shared_ptr<ASTFunctionBlockNode> functionBlockNode, std::shared_ptr<TypeSignature> returnType, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(functionBlockNode->getContents(), returnType, typeCheckerResult);
}

void RequiredReturnExpressionTypeCheckerRule::enforce(std::shared_ptr<ASTIfStatementNode> ifStatementNode, std::shared_ptr<TypeSignature> returnType, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(ifStatementNode->getIfBlock()->getBlock()->getContents(), returnType, typeCheckerResult);

    for (auto elseIfBlock : *ifStatementNode->getElseIfBlocks()) {
        this->checkNode(elseIfBlock->getBlock()->getContents(), returnType, typeCheckerResult);
    }

    if (ifStatementNode->getElseBlock()) {
        this->checkNode(ifStatementNode->getElseBlock().value()->getBlock()->getContents(), returnType, typeCheckerResult);
    }

}

void RequiredReturnExpressionTypeCheckerRule::enforce(std::shared_ptr<ASTTryStatementNode> tryStatementNode, std::shared_ptr<TypeSignature> returnType, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(tryStatementNode->getTryBlock()->getBlock()->getContents(), returnType, typeCheckerResult);
    this->checkNode(tryStatementNode->getCatchBlock()->getBlock()->getContents(), returnType, typeCheckerResult);

    if (tryStatementNode->getFinallyBlock()) {
        this->checkNode(tryStatementNode->getFinallyBlock().value()->getBlock()->getContents(), returnType,  typeCheckerResult);
    }

}

void RequiredReturnExpressionTypeCheckerRule::enforce(std::shared_ptr<ASTForInStatementNode> forStatementNode, std::shared_ptr<TypeSignature> returnType, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(forStatementNode->getBlock()->getContents(), returnType, typeCheckerResult);
}

void RequiredReturnExpressionTypeCheckerRule::enforce(std::shared_ptr<ASTWhileStatementNode> whileStatementNode, std::shared_ptr<TypeSignature> returnType, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(whileStatementNode->getBlock()->getContents(), returnType, typeCheckerResult);
}

TypeCheckerRuleType RequiredReturnExpressionTypeCheckerRule::getType() {
    return REQUIRED_RETURN_EXPRESSION_TCR;
}

std::string RequiredReturnExpressionTypeCheckerRule::toString() {
    return "REQUIRED_RETURN_EXPRESSION";
}

bool RequiredReturnExpressionTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void RequiredReturnExpressionTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}

void RequiredReturnExpressionTypeCheckerRule::checkNode(std::vector<std::shared_ptr<ASTNode>>* nodes, std::shared_ptr<TypeSignature> returnType, TypeCheckerResult* typeCheckerResult) {
    for (auto statement : *nodes) {
        if (statement->is(AST_FUNCTION_RETURN_EXPRESSION_NODE) &&
            !returnType->getTargetTypeSignature()->isEquivalentTo(statement->getTypeSignature()->getTargetTypeSignature())) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::FunctionReturnExpressionMismatch(statement)());
        } else if (statement->is(AST_IF_STATEMENT_NODE)) {
            this->enforce(std::dynamic_pointer_cast<ASTIfStatementNode>(statement), returnType, typeCheckerResult);
        } else if (statement->is(AST_TRY_STATEMENT_NODE)) {
            this->enforce(std::dynamic_pointer_cast<ASTTryStatementNode>(statement), returnType, typeCheckerResult);
        } else if (statement->is(AST_FOR_IN_STATEMENT_NODE)) {
            this->enforce(std::dynamic_pointer_cast<ASTForInStatementNode>(statement), returnType, typeCheckerResult);
        } else if (statement->is(AST_WHILE_STATEMENT_NODE)) {
            this->enforce(std::dynamic_pointer_cast<ASTWhileStatementNode>(statement), returnType, typeCheckerResult);
        }
    }
}