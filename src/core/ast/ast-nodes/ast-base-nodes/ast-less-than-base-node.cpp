//
// Created by Johny Georges on 2024-04-06.
//

#include "ast-less-than-base-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-type-nodes/ast-type-parameter-list-start-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-operator-node.h"

ASTLessThanBaseNode::ASTLessThanBaseNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTLessThanBaseNode::getLexeme() {
    return _lexeme;
}

ASTNode * ASTLessThanBaseNode::transformIfNecessary(std::optional<ASTNode *> prevNode,
                                                    std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {

    if (prevNode && prevNode.value()->isOneOf({ AST_FUNCTION_NODE, AST_PROCEDURE_NODE, AST_TUPLE_NODE, AST_ARRAY_TYPE_KEYWORD_NODE, AST_REF_TYPE_KEYWORD_NODE })) {
        return new ASTTypeParameterListStartNode(this->getLexeme());
    }

    return new ASTBinaryOperatorNode(_lexeme);
}

ASTNodeType ASTLessThanBaseNode::getNodeType() {
    return AST_LESS_THAN_BASE_NODE;
}

std::string ASTLessThanBaseNode::toString() {
    return "LESS_THAN";
}

bool ASTLessThanBaseNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTLessThanBaseNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTLessThanBaseNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}