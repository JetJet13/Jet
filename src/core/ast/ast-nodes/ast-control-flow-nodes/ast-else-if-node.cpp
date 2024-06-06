//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-else-if-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTElseIfNode::ASTElseIfNode(ASTElseNode* elseKeyword, ASTIfNode* ifKeyword) {
    _else = elseKeyword;
    _if = ifKeyword;
}

ASTElseNode* ASTElseIfNode::getElse() {
    return _else;
}

ASTIfNode* ASTElseIfNode::getIf() {
    return _if;
}

Position* ASTElseIfNode::getStartPosition() {
    return _else->getStartPosition();
}

Position* ASTElseIfNode::getEndPosition() {
    return _if->getEndPosition();
}

ASTNodeType ASTElseIfNode::getNodeType() {
    return AST_ELSE_IF_NODE;
}

std::string ASTElseIfNode::toString() {
    return "ELSE_IF";
}

bool ASTElseIfNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTElseIfNode*)other;
    return this->getElse()->isSameAs(otherNode->getElse()) &&
           this->getIf()->isSameAs(otherNode->getIf());
}

void ASTElseIfNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _else->print();
    _if->print();
    Logger::log("----------");
}

std::string ASTElseIfNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_else)
    ->addWithWhitespace(_if);
    return sourceCodeBuilder.build();
}