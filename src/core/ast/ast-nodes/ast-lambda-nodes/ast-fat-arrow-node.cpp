//
// Created by Johny Georges on 2024-04-02.
//

#include "ast-fat-arrow-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFatArrowNode::ASTFatArrowNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTFatArrowNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTFatArrowNode::getNodeType() {
    return AST_FAT_ARROW_NODE;
}

std::string ASTFatArrowNode::toString() {
    return "FAT_ARROW";
}

bool ASTFatArrowNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTFatArrowNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTFatArrowNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}