//
// Created by Johny Georges on 2024-04-02.
//

#include "ast-fat-arrow-base-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-lambda-nodes/ast-lambda-type-fat-arrow-node.h"
#include "../ast-lambda-nodes/ast-lambda-expression-fat-arrow-node.h"

ASTFatArrowBaseNode::ASTFatArrowBaseNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTFatArrowBaseNode::getLexeme() {
    return _lexeme;
}

ASTNode * ASTFatArrowBaseNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_INTERMEDIATE_MODE) {
        return this;
    }

    if (mode == SA_TUPLE_TYPE_MODE || (prevNode && prevNode.value()->is(AST_LAMBDA_TYPE_PARAMETER_LIST_NODE))) {
        return new ASTLambdaTypeFatArrowNode(this->getLexeme());
    }

    return new ASTLambdaExpressionFatArrowNode(this->getLexeme());
}

ASTNodeType ASTFatArrowBaseNode::getNodeType() {
    return AST_FAT_ARROW_BASE_NODE;
}

std::string ASTFatArrowBaseNode::toString() {
    return "FAT_ARROW";
}

bool ASTFatArrowBaseNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTFatArrowBaseNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTFatArrowBaseNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}