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
// Created by Johny Georges on 2024-05-27.
//

#include "all-paths-return-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../types/type-checker-error-message-table.h"


void AllPathsReturnTypeCheckerRule::enforce(std::shared_ptr<ASTFunctionBlockNode> functionBlockNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    if (functionBlockNode->hasReturnExpression()) {
        return;
    }

    if (!this->verifyAllBlockPathsReturn(functionBlockNode->getContents())) {
        typeCheckerResult->addError(message());
    }
}

TypeCheckerRuleType AllPathsReturnTypeCheckerRule::getType() {
    return ALL_PATHS_RETURN_TCR;
}

std::string AllPathsReturnTypeCheckerRule::toString() {
    return "ALL_PATHS_RETURN";
}

bool AllPathsReturnTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void AllPathsReturnTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}

bool AllPathsReturnTypeCheckerRule::verifyAllIfStatementPathsReturn(std::shared_ptr<ASTIfStatementNode> ifStatementNode) {
    if (!ifStatementNode->getElseBlock()) {
        return false;
    }


    if (!ifStatementNode->getIfBlock()->getBlock()->hasReturnExpression() &&
        !this->verifyAllBlockPathsReturn(ifStatementNode->getIfBlock()->getBlock()->getContents())) {
        return false;
    }

    for (auto elseIfBlock : *ifStatementNode->getElseIfBlocks()) {
        if (!elseIfBlock->getBlock()->hasReturnExpression() &&
            !this->verifyAllBlockPathsReturn(elseIfBlock->getBlock()->getContents())) {
            return false;
        }
    }


    if (!ifStatementNode->getElseBlock().value()->getBlock()->hasReturnExpression() &&
        !this->verifyAllBlockPathsReturn(ifStatementNode->getElseBlock().value()->getBlock()->getContents())) {
        return false;
    }

    return true;
}

bool AllPathsReturnTypeCheckerRule::verifyAllTryStatementPathsReturn(std::shared_ptr<ASTTryStatementNode> tryStatementNode) {
    auto tryBlockDoesNotReturn = !tryStatementNode->getTryBlock()->getBlock()->hasReturnExpression() &&
                                 !this->verifyAllBlockPathsReturn(tryStatementNode->getTryBlock()->getBlock()->getContents());

    auto catchBlockDoesNotReturn = !tryStatementNode->getCatchBlock()->getBlock()->hasReturnExpression() &&
                                 !this->verifyAllBlockPathsReturn(tryStatementNode->getCatchBlock()->getBlock()->getContents());


    if (tryStatementNode->getFinallyBlock() &&
        (
            tryStatementNode->getFinallyBlock().value()->getBlock()->hasReturnExpression() ||
            this->verifyAllBlockPathsReturn(tryStatementNode->getFinallyBlock().value()->getBlock()->getContents()))
        ) {
        return true;
    }

    if (tryBlockDoesNotReturn || catchBlockDoesNotReturn) {
        return false;
    }

    return true;
}

bool AllPathsReturnTypeCheckerRule::verifyAllBlockPathsReturn(std::vector<std::shared_ptr<ASTNode>>* blockContents) {
    auto pathsReturnResults = std::vector<bool>();
    for (auto node : *blockContents) {

        if (node->is(AST_IF_STATEMENT_NODE)) {
            auto ifStatementNode = std::dynamic_pointer_cast<ASTIfStatementNode>(node);
            if (ifStatementNode->getElseBlock()) {
                pathsReturnResults.push_back(
                        this->verifyAllIfStatementPathsReturn(ifStatementNode)
                );
            }
        }

        if (node->is(AST_TRY_STATEMENT_NODE)) {
            pathsReturnResults.push_back(
                    this->verifyAllTryStatementPathsReturn(std::dynamic_pointer_cast<ASTTryStatementNode>(node))
            );
        }
    }
    return this->verifyAllPathsReturn(&pathsReturnResults);
}

bool AllPathsReturnTypeCheckerRule::verifyAllPathsReturn(std::vector<bool>* allPathsReturnResults) {
    if (allPathsReturnResults->empty()) {
        return false;
    }

    for (auto result : *allPathsReturnResults) {
        if (!result) {
            return false;
        }
    }
    return true;

}