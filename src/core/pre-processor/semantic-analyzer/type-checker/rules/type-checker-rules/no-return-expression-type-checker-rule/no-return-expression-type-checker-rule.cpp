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

#include "no-return-expression-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../types/type-checker-error-message-table.h"

void NoReturnExpressionTypeCheckerRule::enforce(std::shared_ptr<ASTFunctionBlockNode> functionBlockNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(functionBlockNode->getContents(), message, typeCheckerResult);
}

void NoReturnExpressionTypeCheckerRule::enforce(std::shared_ptr<ASTIfStatementNode> ifStatementNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(ifStatementNode->getIfBlock()->getBlock()->getContents(), message, typeCheckerResult);

    for (auto elseIfBlock : *ifStatementNode->getElseIfBlocks()) {
        this->checkNode(elseIfBlock->getBlock()->getContents(), message, typeCheckerResult);
    }

    if (ifStatementNode->getElseBlock()) {
        this->checkNode(ifStatementNode->getElseBlock().value()->getBlock()->getContents(), message, typeCheckerResult);
    }

}

void NoReturnExpressionTypeCheckerRule::enforce(std::shared_ptr<ASTTryStatementNode> tryStatementNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(tryStatementNode->getTryBlock()->getBlock()->getContents(), message, typeCheckerResult);
    this->checkNode(tryStatementNode->getCatchBlock()->getBlock()->getContents(), message, typeCheckerResult);

    if (tryStatementNode->getFinallyBlock()) {
        this->checkNode(tryStatementNode->getFinallyBlock().value()->getBlock()->getContents(), message, typeCheckerResult);
    }

}

void NoReturnExpressionTypeCheckerRule::enforce(std::shared_ptr<ASTForInStatementNode> forStatementNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(forStatementNode->getBlock()->getContents(), message, typeCheckerResult);
}

void NoReturnExpressionTypeCheckerRule::enforce(std::shared_ptr<ASTWhileStatementNode> whileStatementNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(whileStatementNode->getBlock()->getContents(), message, typeCheckerResult);
}


TypeCheckerRuleType NoReturnExpressionTypeCheckerRule::getType() {
    return NO_RETURN_EXPRESSION_TCR;
}

std::string NoReturnExpressionTypeCheckerRule::toString() {
    return "NO_RETURN_EXPRESSION";
}

bool NoReturnExpressionTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void NoReturnExpressionTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}

void NoReturnExpressionTypeCheckerRule::checkNode(std::vector<std::shared_ptr<ASTNode>>* nodes, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    for (auto statement : *nodes) {
        if (statement->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
            auto functionReturnExpression = std::dynamic_pointer_cast<ASTFunctionReturnExpressionNode>(statement);
            if (functionReturnExpression->hasExpression()) {
                typeCheckerResult->addError(message());
            }
        } else if (statement->is(AST_IF_STATEMENT_NODE)) {
            this->enforce(std::dynamic_pointer_cast<ASTIfStatementNode>(statement), message, typeCheckerResult);
        } else if (statement->is(AST_TRY_STATEMENT_NODE)) {
            this->enforce(std::dynamic_pointer_cast<ASTTryStatementNode>(statement), message, typeCheckerResult);
        } else if (statement->is(AST_FOR_IN_STATEMENT_NODE)) {
            this->enforce(std::dynamic_pointer_cast<ASTForInStatementNode>(statement), message, typeCheckerResult);
        } else if (statement->is(AST_WHILE_STATEMENT_NODE)) {
            this->enforce(std::dynamic_pointer_cast<ASTWhileStatementNode>(statement), message, typeCheckerResult);
        }
    }
}