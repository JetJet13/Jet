//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTupleNode::ASTTupleNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTTupleNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTTupleNode::getNodeType() {
    return AST_TUPLE_NODE;
}

std::string ASTTupleNode::toString() {
    return "TUPLE";
}

bool ASTTupleNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTTupleNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTTupleNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}