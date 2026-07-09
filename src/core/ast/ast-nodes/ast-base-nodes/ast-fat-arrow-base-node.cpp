//
// Created by Johny Georges on 2024-04-02.
//

#include "ast-fat-arrow-base-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-lambda-nodes/ast-lambda-type-fat-arrow-node.h"
#include "../ast-lambda-nodes/ast-lambda-expression-fat-arrow-node.h"

ASTFatArrowBaseNode::ASTFatArrowBaseNode(std::shared_ptr<Lexeme> lexeme) {
    _lexeme = lexeme;
}

std::shared_ptr<Lexeme> ASTFatArrowBaseNode::getLexeme() {
    return _lexeme;
}

std::shared_ptr<ASTNode> ASTFatArrowBaseNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->is(AST_LAMBDA_TYPE_PARAMETER_LIST_NODE)) {
        return std::make_shared<ASTLambdaTypeFatArrowNode>(this->getLexeme());
    }

    return std::make_shared<ASTLambdaExpressionFatArrowNode>(this->getLexeme());
}

ASTNodeType ASTFatArrowBaseNode::getNodeType() {
    return AST_FAT_ARROW_BASE_NODE;
}

std::string ASTFatArrowBaseNode::toString() {
    return "FAT_ARROW";
}

bool ASTFatArrowBaseNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTFatArrowBaseNode>(other);
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTFatArrowBaseNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}