//
// Created by Johny Georges on 2024-05-25.
//

#include "no-return-expression-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../types/type-checker-error-message-table.h"

void NoReturnExpressionTypeCheckerRule::enforce(ASTFunctionBlockNode* functionBlockNode, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(functionBlockNode->getContents(), typeCheckerResult);
}

void NoReturnExpressionTypeCheckerRule::enforce(ASTIfStatementNode* ifStatementNode, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(ifStatementNode->getIfBlock()->getBlock()->getContents(), typeCheckerResult);

    for (auto elseIfBlock : *ifStatementNode->getElseIfBlocks()) {
        this->checkNode(elseIfBlock->getBlock()->getContents(), typeCheckerResult);
    }

    if (ifStatementNode->getElseBlock()) {
        this->checkNode(ifStatementNode->getElseBlock().value()->getBlock()->getContents(), typeCheckerResult);
    }

}

void NoReturnExpressionTypeCheckerRule::enforce(ASTTryStatementNode* tryStatementNode, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(tryStatementNode->getTryBlock()->getBlock()->getContents(), typeCheckerResult);
    this->checkNode(tryStatementNode->getCatchBlock()->getBlock()->getContents(), typeCheckerResult);

    if (tryStatementNode->getFinallyBlock()) {
        this->checkNode(tryStatementNode->getFinallyBlock().value()->getBlock()->getContents(), typeCheckerResult);
    }

}

void NoReturnExpressionTypeCheckerRule::enforce(ASTForStatementNode* forStatementNode, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(forStatementNode->getBlock()->getContents(), typeCheckerResult);
}

void NoReturnExpressionTypeCheckerRule::enforce(ASTWhileStatementNode* whileStatementNode, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(whileStatementNode->getBlock()->getContents(), typeCheckerResult);
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

void NoReturnExpressionTypeCheckerRule::checkNode(std::vector<ASTNode*>* nodes, TypeCheckerResult* typeCheckerResult) {
    for (auto statement : *nodes) {
        if (statement->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::ProcedureHasReturnExpression);
        } else if (statement->is(AST_IF_STATEMENT_NODE)) {
            this->enforce((ASTIfStatementNode*)statement, typeCheckerResult);
        } else if (statement->is(AST_TRY_STATEMENT_NODE)) {
            this->enforce((ASTTryStatementNode*)statement, typeCheckerResult);
        } else if (statement->is(AST_FOR_STATEMENT_NODE)) {
            this->enforce((ASTForStatementNode*)statement, typeCheckerResult);
        } else if (statement->is(AST_WHILE_STATEMENT_NODE)) {
            this->enforce((ASTWhileStatementNode*)statement, typeCheckerResult);
        }
    }
}