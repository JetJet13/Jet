//
// Created by Johny Georges on 2024-04-05.
//

#include "ast-lambda-type-fat-arrow-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTLambdaTypeFatArrowNode::ASTLambdaTypeFatArrowNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTLambdaTypeFatArrowNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTLambdaTypeFatArrowNode::getNodeType() {
    return AST_LAMBDA_TYPE_FAT_ARROW_NODE;
}

std::string ASTLambdaTypeFatArrowNode::toString() {
    return "LAMBDA_TYPE_FAT_ARROW";
}

bool ASTLambdaTypeFatArrowNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTLambdaTypeFatArrowNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTLambdaTypeFatArrowNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}