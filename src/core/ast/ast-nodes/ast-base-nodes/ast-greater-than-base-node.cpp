//
// Created by Johny Georges on 2024-04-06.
//

#include "ast-greater-than-base-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-lambda-nodes/ast-lambda-type-fat-arrow-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-arithmetic-operator-node.h"
#include "../ast-type-nodes/ast-type-parameter-list-end-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-comparator-operator-node.h"

ASTGreaterThanBaseNode::ASTGreaterThanBaseNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTGreaterThanBaseNode::getLexeme() {
    return _lexeme;
}

ASTNode * ASTGreaterThanBaseNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {

    if (mode == SA_TYPE_PARAMETER_LIST_MODE) {
        return new ASTTypeParameterListEndNode(this->getLexeme());
    }

    return new ASTBinaryComparatorOperatorNode(_lexeme);
}

ASTNodeType ASTGreaterThanBaseNode::getNodeType() {
    return AST_GREATER_THAN_BASE_NODE;
}

std::string ASTGreaterThanBaseNode::toString() {
    return "GREATER_THAN";
}

bool ASTGreaterThanBaseNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTGreaterThanBaseNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTGreaterThanBaseNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}