//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-enum-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTEnumNameNode::ASTEnumNameNode(Lexeme *lexeme) {
    _name = lexeme;
}

ASTEnumNameNode::ASTEnumNameNode(Lexeme *lexeme, std::string id) {
    _name = lexeme;
    _id = id;
}

Lexeme* ASTEnumNameNode::getName() {
    return _name;
}

ASTNodeType ASTEnumNameNode::getNodeType() {
    return AST_ENUM_NAME_NODE;
}

std::string ASTEnumNameNode::toString() {
    return "ENUM_NAME";
}

bool ASTEnumNameNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTEnumNameNode*)other;
    return this->getName()->hasSameSymbolTypeAs(otherNode->getName());
}

void ASTEnumNameNode::print() {
    Logger::log(this->toString(), "-", _name->toString());
}