//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-custom-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTCustomTypeNode::ASTCustomTypeNode(Lexeme* lexeme, std::string id) {
    _lexeme = lexeme;
    this->setId(id);
}

Lexeme* ASTCustomTypeNode::getLexeme() {
    return _lexeme;
}

Position* ASTCustomTypeNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

Position* ASTCustomTypeNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

ASTNodeType ASTCustomTypeNode::getNodeType() {
    return AST_CUSTOM_TYPE_NODE;
}

std::string ASTCustomTypeNode::toString() {
    return "CUSTOM_TYPE";
}

bool ASTCustomTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTCustomTypeNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTCustomTypeNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}

std::string ASTCustomTypeNode::toSourceCode() {
    return _id;
}