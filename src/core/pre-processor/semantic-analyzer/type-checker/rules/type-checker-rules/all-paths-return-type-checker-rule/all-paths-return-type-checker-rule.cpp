//
// Created by Johny Georges on 2024-05-27.
//

#include "all-paths-return-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../types/type-checker-error-message-table.h"


void AllPathsReturnTypeCheckerRule::enforce(ASTFunctionBlockNode* functionBlockNode, std::string message, TypeCheckerResult* typeCheckerResult) {
    if (functionBlockNode->hasReturnExpression()) {
        return;
    }

    if (!this->verifyAllBlockPathsReturn(functionBlockNode->getContents())) {
        typeCheckerResult->addError(message);
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

bool AllPathsReturnTypeCheckerRule::verifyAllIfStatementPathsReturn(ASTIfStatementNode* ifStatementNode) {
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

bool AllPathsReturnTypeCheckerRule::verifyAllTryStatementPathsReturn(ASTTryStatementNode* tryStatementNode) {
    auto tryBlockDoesNotReturn = !tryStatementNode->getTryBlock()->getBlock()->hasReturnExpression() &&
                                 !this->verifyAllBlockPathsReturn(tryStatementNode->getTryBlock()->getBlock()->getContents());

    auto catchBlockDoesNotReturn = !tryStatementNode->getCatchBlock()->getBlock()->hasReturnExpression() &&
                                 !this->verifyAllBlockPathsReturn(tryStatementNode->getCatchBlock()->getBlock()->getContents());


    if (tryStatementNode->getFinallyBlock() &&
        !tryStatementNode->getFinallyBlock().value()->getBlock()->hasReturnExpression() &&
        !this->verifyAllBlockPathsReturn(tryStatementNode->getFinallyBlock().value()->getBlock()->getContents())) {
        return false;
    } else if (tryBlockDoesNotReturn || catchBlockDoesNotReturn) {
        return false;
    }

    return true;
}

bool AllPathsReturnTypeCheckerRule::verifyAllBlockPathsReturn(std::vector<ASTNode*>* blockContents) {
    auto pathsReturnResults = std::vector<bool>();
    for (auto node : *blockContents) {

        if (node->is(AST_IF_STATEMENT_NODE)) {
            auto ifStatementNode = (ASTIfStatementNode*)node;
            if (ifStatementNode->getElseBlock()) {
                pathsReturnResults.push_back(
                        this->verifyAllIfStatementPathsReturn(ifStatementNode)
                );
            }
        }

        if (node->is(AST_TRY_STATEMENT_NODE)) {
            pathsReturnResults.push_back(
                    this->verifyAllTryStatementPathsReturn((ASTTryStatementNode*) node)
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