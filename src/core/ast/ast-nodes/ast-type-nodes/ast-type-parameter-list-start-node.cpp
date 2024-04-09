//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-type-parameter-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTypeParameterListStartNode::ASTTypeParameterListStartNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTTypeParameterListStartNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTTypeParameterListStartNode::getNodeType() {
    return AST_TYPE_PARAMETER_LIST_START_NODE;
}

std::string ASTTypeParameterListStartNode::toString() {
    return "TYPE_PARAMETER_LIST_START";
}

bool ASTTypeParameterListStartNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTTypeParameterListStartNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTTypeParameterListStartNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}