//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTupleListStartNode::ASTTupleListStartNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTTupleListStartNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTTupleListStartNode::getNodeType() {
    return AST_TUPLE_LIST_START_NODE;
}

std::string ASTTupleListStartNode::toString() {
    return "TUPLE_START";
}

bool ASTTupleListStartNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTTupleListStartNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTTupleListStartNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}