//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-lambda-type-parameter-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTLambdaTypeParameterListStartNode::ASTLambdaTypeParameterListStartNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTLambdaTypeParameterListStartNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTLambdaTypeParameterListStartNode::getNodeType() {
    return AST_LAMBDA_TYPE_PARAMETER_LIST_START_NODE;
}

std::string ASTLambdaTypeParameterListStartNode::toString() {
    return "LAMBDA_TYPE_PARAMETER_LIST_START";
}

bool ASTLambdaTypeParameterListStartNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTLambdaTypeParameterListStartNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTLambdaTypeParameterListStartNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}