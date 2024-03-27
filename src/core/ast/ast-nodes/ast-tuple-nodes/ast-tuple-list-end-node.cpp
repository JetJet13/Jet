//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTupleListEndNode::ASTTupleListEndNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTTupleListEndNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTTupleListEndNode::getNodeType() {
    return AST_TUPLE_LIST_END_NODE;
}

std::string ASTTupleListEndNode::toString() {
    return "TUPLE_END";
}

bool ASTTupleListEndNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTTupleListEndNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTTupleListEndNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}