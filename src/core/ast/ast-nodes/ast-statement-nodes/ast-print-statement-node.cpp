//
// Created by Johny Georges on 2025-07-21.
//

#include "ast-print-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTPrintStatementNode::ASTPrintStatementNode(ASTPrintNode* print, ASTFunctionArgumentListNode* arguments) {
    _print = print;
    _arguments = arguments;
    _children.push_back(_arguments);
}

ASTFunctionArgumentListNode* ASTPrintStatementNode::getArguments() {
    return _arguments;
}

Position* ASTPrintStatementNode::getStartPosition() {
    return _arguments->getStartPosition();
}

Position* ASTPrintStatementNode::getEndPosition() {
    return _arguments->getEndPosition();
}

ASTNodeType ASTPrintStatementNode::getNodeType() {
    return AST_PRINT_STATEMENT_NODE;
}

std::string ASTPrintStatementNode::toString() {
    return "PRINT_STATEMENT";
}

bool ASTPrintStatementNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTPrintStatementNode*)other;
    return this->getArguments()->isSameAs(otherNode->getArguments());
}

void ASTPrintStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _arguments->print();
    Logger::log("----------");
}

std::string ASTPrintStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_print)->add(_arguments);
    return sourceCodeBuilder.build();
}