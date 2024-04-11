//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-int-literal-node.h"
#include "../ast-tuple-nodes/ast-tuple-access-node.h"
#include "../ast-type-nodes/ast-type-node-factory.h"

ASTNode * ASTIntLiteralNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode,
                                                  SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->is(AST_PERIOD_NODE)) {
        return new ASTTupleAccessNode(_lexemeLiteral);
    }

    if (mode == SA_TYPE_PARAMETER_LIST_MODE) {
        return ASTTypeNodeFactory::createIntLiteralTypeNode(_lexemeLiteral);
    }

    return this;
}

ASTNodeType ASTIntLiteralNode::getNodeType() {
    return AST_INT_LITERAL_NODE;
}

std::string ASTIntLiteralNode::toString() {
    return "INT_LITERAL - " + _lexemeLiteral->toString();
}
