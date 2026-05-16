//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-int-literal-node.h"
#include "../ast-tuple-nodes/ast-tuple-access-node.h"

ASTNode * ASTIntLiteralNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->is(AST_PERIOD_NODE)) {
        return (new ASTTupleAccessNode(_lexeme))->setIndexValue(this->getValue());
    }

    return this;
}

ASTNodeType ASTIntLiteralNode::getNodeType() {
    return AST_INT_LITERAL_NODE;
}

std::string ASTIntLiteralNode::toString() {
    return "INT_LITERAL - " + _lexeme->toString();
}

void ASTIntLiteralNode::setValue(TokenTable* tokenTable) {
    _value = tokenTable->getInt(_lexeme->getToken()->getValueId().value());
}

std::string ASTIntLiteralNode::getValue() {
    return _value;
}
