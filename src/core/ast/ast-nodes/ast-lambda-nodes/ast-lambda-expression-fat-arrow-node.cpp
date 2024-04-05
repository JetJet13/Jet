//
// Created by Johny Georges on 2024-04-05.
//

#include "ast-lambda-expression-fat-arrow-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTLambdaExpressionFatArrowNode::ASTLambdaExpressionFatArrowNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTLambdaExpressionFatArrowNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTLambdaExpressionFatArrowNode::getNodeType() {
    return AST_LAMBDA_EXPRESSION_FAT_ARROW_NODE;
}

std::string ASTLambdaExpressionFatArrowNode::toString() {
    return "LAMBDA_EXPRESSION_FAT_ARROW";
}

bool ASTLambdaExpressionFatArrowNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTLambdaExpressionFatArrowNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTLambdaExpressionFatArrowNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}