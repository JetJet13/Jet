//
// Created by Johny Georges on 2024-05-25.
//

#include "required-return-expression-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../types/type-checker-error-message-table.h"

void RequiredReturnExpressionTypeCheckerRule::enforce(ASTFunctionBlockNode* functionBlockNode, TypeSignature* returnType, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(functionBlockNode->getContents(), returnType, typeCheckerResult);
}

void RequiredReturnExpressionTypeCheckerRule::enforce(ASTIfStatementNode* ifStatementNode, TypeSignature* returnType, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(ifStatementNode->getIfBlock()->getBlock()->getContents(), returnType, typeCheckerResult);

    for (auto elseIfBlock : *ifStatementNode->getElseIfBlocks()) {
        this->checkNode(elseIfBlock->getBlock()->getContents(), returnType, typeCheckerResult);
    }

    if (ifStatementNode->getElseBlock()) {
        this->checkNode(ifStatementNode->getElseBlock().value()->getBlock()->getContents(), returnType, typeCheckerResult);
    }

}

void RequiredReturnExpressionTypeCheckerRule::enforce(ASTTryStatementNode* tryStatementNode, TypeSignature* returnType, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(tryStatementNode->getTryBlock()->getBlock()->getContents(), returnType, typeCheckerResult);
    this->checkNode(tryStatementNode->getCatchBlock()->getBlock()->getContents(), returnType, typeCheckerResult);

    if (tryStatementNode->getFinallyBlock()) {
        this->checkNode(tryStatementNode->getFinallyBlock().value()->getBlock()->getContents(), returnType,  typeCheckerResult);
    }

}

void RequiredReturnExpressionTypeCheckerRule::enforce(ASTForInStatementNode* forStatementNode, TypeSignature* returnType, TypeCheckerResult* typeCheckerResult) {
    this->checkNode(forStatementNode->getBlock()->getContents(), returnType, typeCheckerResult);
}

void RequiredReturnExpressionTypeCheckerRule::enforce(ASTWhileStatementNode* whileStatementNode, TypeSignature* returnType, TypeCheckerResult* typeCheckerResult) {
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

void RequiredReturnExpressionTypeCheckerRule::checkNode(std::vector<ASTNode*>* nodes, TypeSignature* returnType, TypeCheckerResult* typeCheckerResult) {
    for (auto statement : *nodes) {
        if (statement->is(AST_FUNCTION_RETURN_EXPRESSION_NODE) &&
            !statement->getTypeSignature()->getTargetTypeSignature()->isEquivalentTo(returnType)) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::FunctionReturnExpressionMismatch(statement)());
        } else if (statement->is(AST_IF_STATEMENT_NODE)) {
            this->enforce((ASTIfStatementNode*)statement, returnType, typeCheckerResult);
        } else if (statement->is(AST_TRY_STATEMENT_NODE)) {
            this->enforce((ASTTryStatementNode*)statement, returnType, typeCheckerResult);
        } else if (statement->is(AST_FOR_IN_STATEMENT_NODE)) {
            this->enforce((ASTForInStatementNode*)statement, returnType, typeCheckerResult);
        } else if (statement->is(AST_WHILE_STATEMENT_NODE)) {
            this->enforce((ASTWhileStatementNode*)statement, returnType, typeCheckerResult);
        }
    }
}