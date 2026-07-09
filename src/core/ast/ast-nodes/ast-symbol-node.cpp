//
// Created by Johny Georges on 2024-04-18.
//

#include "ast-symbol-node.h"
#include "../../../shared/utils/logger/logger.h"

ASTSymbolNode::ASTSymbolNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

ASTSymbolNode::ASTSymbolNode(Lexeme *lexeme, std::string id) {
    _lexeme = lexeme;
    _id = id;
}

Lexeme* ASTSymbolNode::getLexeme() {
    return _lexeme;
}

std::shared_ptr<Position> ASTSymbolNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

std::shared_ptr<Position> ASTSymbolNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

bool ASTSymbolNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTSymbolNode>(other);
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTSymbolNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString(), "|", "id:", _id);
}

std::string ASTSymbolNode::toSourceCode() {
    return this->getLexeme()->getToken()->getRawValue();
}