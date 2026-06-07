//
// Created by Johny Georges on 2024-04-05.
//

#include "ast-lambda-expression-fat-arrow-node.h"
#include "ast-lambda-type-fat-arrow-node.h"

ASTNode* ASTLambdaExpressionFatArrowNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_TUPLE_TYPE_MODE) {
        return new ASTLambdaTypeFatArrowNode(_lexeme);
    }
    return this;
}

ASTNodeType ASTLambdaExpressionFatArrowNode::getNodeType() {
    return AST_LAMBDA_EXPRESSION_FAT_ARROW_NODE;
}

std::string ASTLambdaExpressionFatArrowNode::toString() {
    return "LAMBDA_EXPRESSION_FAT_ARROW";
}