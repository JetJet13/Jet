//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-type-parameter-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTypeParameterListEndNode::ASTTypeParameterListEndNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTTypeParameterListEndNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTTypeParameterListEndNode::getNodeType() {
    return AST_TYPE_PARAMETER_LIST_END_NODE;
}

std::string ASTTypeParameterListEndNode::toString() {
    return "TYPE_PARAMETER_LIST_END";
}

bool ASTTypeParameterListEndNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTTypeParameterListEndNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTTypeParameterListEndNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}