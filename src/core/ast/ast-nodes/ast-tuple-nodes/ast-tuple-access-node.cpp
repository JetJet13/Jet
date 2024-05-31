//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-access-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTupleAccessNode::ASTTupleAccessNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTTupleAccessNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTTupleAccessNode::getNodeType() {
    return AST_TUPLE_ACCESS_NODE;
}

std::string ASTTupleAccessNode::toString() {
    return "TUPLE_ACCESS";
}

bool ASTTupleAccessNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTTupleAccessNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTTupleAccessNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}

std::string ASTTupleAccessNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}

ASTTupleAccessNode* ASTTupleAccessNode::setIndexValue(int index) {
    _index = index;
    return this;
}

int ASTTupleAccessNode::getIndexValue() {
    return _index;
}