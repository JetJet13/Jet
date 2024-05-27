//
// Created by Johny Georges on 2024-05-27.
//

#include "all-paths-return-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../types/type-checker-error-message-table.h"


void AllPathsReturnTypeCheckerRule::enforce(ASTFunctionBlockNode* functionBlockNode, TypeCheckerResult* typeCheckerResult) {
    if (functionBlockNode->hasReturnExpression()) {
        return;
    }

    auto allPathsReturn = true;
    for (auto node : *functionBlockNode->getContents()) {
        if (node->is(AST_IF_STATEMENT_NODE) && !this->verifyAllIfStatementPathsReturn((ASTIfStatementNode *) node)) {
            allPathsReturn = false;
            break;
        }

        if (node->is(AST_TRY_STATEMENT_NODE) && !this->verifyAllTryStatementPathsReturn((ASTTryStatementNode *) node)) {
            allPathsReturn = false;
            break;
        }
    }


    if (!allPathsReturn) {
        typeCheckerResult->addError(TypeCheckerErrorMessageTable::FunctionNotAllPathsReturn);
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

    auto ifBlockReturns = ifStatementNode->getIfBlock()->getBlock()->hasReturnExpression();
    auto elseBlockReturns = ifStatementNode->getElseBlock().value()->getBlock()->hasReturnExpression();

    if (ifBlockReturns && elseBlockReturns && ifStatementNode->getElseIfBlocks()->empty()) {
        return true;
    }

    if (!ifBlockReturns) {
        for (auto node : *ifStatementNode->getIfBlock()->getBlock()->getContents()) {
            if (node->is(AST_IF_STATEMENT_NODE) && !this->verifyAllIfStatementPathsReturn((ASTIfStatementNode *) node)) {
                return false;
            }

            if (node->is(AST_TRY_STATEMENT_NODE) && !this->verifyAllTryStatementPathsReturn((ASTTryStatementNode *) node)) {
                return false;
            }
        }
    }

    for (auto elseIfBlock : *ifStatementNode->getElseIfBlocks()) {
        if (elseIfBlock->getBlock()->hasReturnExpression()) {
            continue;
        } else {
            for (auto node : *elseIfBlock->getBlock()->getContents()) {
                if (node->is(AST_IF_STATEMENT_NODE) && !this->verifyAllIfStatementPathsReturn((ASTIfStatementNode *) node)) {
                    return false;
                }

                if (node->is(AST_TRY_STATEMENT_NODE) && !this->verifyAllTryStatementPathsReturn((ASTTryStatementNode *) node)) {
                    return false;
                }
            }
        }
    }

    if (!elseBlockReturns) {
        for (auto node : *ifStatementNode->getElseBlock().value()->getBlock()->getContents()) {
            if (node->is(AST_IF_STATEMENT_NODE) && !this->verifyAllIfStatementPathsReturn((ASTIfStatementNode *) node)) {
                return false;
            }

            if (node->is(AST_TRY_STATEMENT_NODE) && !this->verifyAllTryStatementPathsReturn((ASTTryStatementNode *) node)) {
                return false;
            }
        }
    }

    return true;
}

bool AllPathsReturnTypeCheckerRule::verifyAllTryStatementPathsReturn(ASTTryStatementNode* tryStatementNode) {
    auto tryBlockReturns = tryStatementNode->getTryBlock()->getBlock()->hasReturnExpression();
    auto catchBlockReturns = tryStatementNode->getCatchBlock()->getBlock()->hasReturnExpression();
    auto finallyBlockReturns = true;

    if (tryStatementNode->getFinallyBlock()) {
        finallyBlockReturns = tryStatementNode->getFinallyBlock().value()->getBlock()->hasReturnExpression();
    }

    if (tryBlockReturns && catchBlockReturns && finallyBlockReturns) {
        return true;
    }

    if (!tryBlockReturns) {
        for (auto node : *tryStatementNode->getTryBlock()->getBlock()->getContents()) {
            if (node->is(AST_IF_STATEMENT_NODE) && !this->verifyAllIfStatementPathsReturn((ASTIfStatementNode *) node)) {
                return false;
            }

            if (node->is(AST_TRY_STATEMENT_NODE) && !this->verifyAllTryStatementPathsReturn((ASTTryStatementNode *) node)) {
                return false;
            }
        }

    }

    if (!catchBlockReturns) {
        for (auto node : *tryStatementNode->getCatchBlock()->getBlock()->getContents()) {
            if (node->is(AST_IF_STATEMENT_NODE) && !this->verifyAllIfStatementPathsReturn((ASTIfStatementNode *) node)) {
                return false;
            }

            if (node->is(AST_TRY_STATEMENT_NODE) && !this->verifyAllTryStatementPathsReturn((ASTTryStatementNode *) node)) {
                return false;
            }
        }

    }


   if (tryStatementNode->getFinallyBlock() && !finallyBlockReturns) {
       for (auto node : *tryStatementNode->getTryBlock()->getBlock()->getContents()) {
           if (node->is(AST_IF_STATEMENT_NODE) && !this->verifyAllIfStatementPathsReturn((ASTIfStatementNode *) node)) {
               return false;
           }

           if (node->is(AST_TRY_STATEMENT_NODE) && !this->verifyAllTryStatementPathsReturn((ASTTryStatementNode *) node)) {
               return false;
           }
       }
   }

    return true;
}