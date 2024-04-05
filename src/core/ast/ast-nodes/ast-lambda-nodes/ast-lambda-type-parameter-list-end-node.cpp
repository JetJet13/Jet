//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-lambda-type-parameter-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTLambdaTypeParameterListEndNode::ASTLambdaTypeParameterListEndNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTLambdaTypeParameterListEndNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTLambdaTypeParameterListEndNode::getNodeType() {
    return AST_LAMBDA_TYPE_PARAMETER_LIST_END_NODE;
}

std::string ASTLambdaTypeParameterListEndNode::toString() {
    return "LAMBDA_TYPE_PARAMETER_LIST_END";
}

bool ASTLambdaTypeParameterListEndNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTLambdaTypeParameterListEndNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTLambdaTypeParameterListEndNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}