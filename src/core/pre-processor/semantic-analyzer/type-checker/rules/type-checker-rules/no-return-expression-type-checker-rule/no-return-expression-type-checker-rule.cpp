//
// Created by Johny Georges on 2024-05-25.
//

#include "no-return-expression-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../types/type-checker-error-message-table.h"

void NoReturnExpressionTypeCheckerRule::enforce(ASTFunctionBlockNode* functionBlockNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(functionBlockNode->getContents(), message, typeCheckerResult);
}

void NoReturnExpressionTypeCheckerRule::enforce(ASTIfStatementNode* ifStatementNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(ifStatementNode->getIfBlock()->getBlock()->getContents(), message, typeCheckerResult);

    for (auto elseIfBlock : *ifStatementNode->getElseIfBlocks()) {
        this->checkNode(elseIfBlock->getBlock()->getContents(), message, typeCheckerResult);
    }

    if (ifStatementNode->getElseBlock()) {
        this->checkNode(ifStatementNode->getElseBlock().value()->getBlock()->getContents(), message, typeCheckerResult);
    }

}

void NoReturnExpressionTypeCheckerRule::enforce(ASTTryStatementNode* tryStatementNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(tryStatementNode->getTryBlock()->getBlock()->getContents(), message, typeCheckerResult);
    this->checkNode(tryStatementNode->getCatchBlock()->getBlock()->getContents(), message, typeCheckerResult);

    if (tryStatementNode->getFinallyBlock()) {
        this->checkNode(tryStatementNode->getFinallyBlock().value()->getBlock()->getContents(), message, typeCheckerResult);
    }

}

void NoReturnExpressionTypeCheckerRule::enforce(ASTForInStatementNode* forStatementNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(forStatementNode->getBlock()->getContents(), message, typeCheckerResult);
}

void NoReturnExpressionTypeCheckerRule::enforce(ASTWhileStatementNode* whileStatementNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
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

void NoReturnExpressionTypeCheckerRule::checkNode(std::vector<ASTNode*>* nodes, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    for (auto statement : *nodes) {
        if (statement->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
            typeCheckerResult->addError(message());
        } else if (statement->is(AST_IF_STATEMENT_NODE)) {
            this->enforce((ASTIfStatementNode*)statement, message, typeCheckerResult);
        } else if (statement->is(AST_TRY_STATEMENT_NODE)) {
            this->enforce((ASTTryStatementNode*)statement, message, typeCheckerResult);
        } else if (statement->is(AST_FOR_IN_STATEMENT_NODE)) {
            this->enforce((ASTForInStatementNode*)statement, message, typeCheckerResult);
        } else if (statement->is(AST_WHILE_STATEMENT_NODE)) {
            this->enforce((ASTWhileStatementNode*)statement, message, typeCheckerResult);
        }
    }
}