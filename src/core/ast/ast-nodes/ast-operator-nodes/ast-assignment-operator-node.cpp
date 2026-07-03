//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-assignment-operator-node.h"
#include "../ast-type-nodes/ast-type-assignment-operator-node.h"

ASTNode* ASTAssignmentOperatorNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({ AST_TYPE_NAME_NODE })) {
        return new ASTTypeAssignmentOperatorNode(this->getLexeme());
    }
    return this;
}

ASTNodeType ASTAssignmentOperatorNode::getNodeType() {
    return AST_ASSIGNMENT_OPERATOR_NODE;
}

std::string ASTAssignmentOperatorNode::toString() {
    return "ASSIGNMENT_OPERATOR";
}