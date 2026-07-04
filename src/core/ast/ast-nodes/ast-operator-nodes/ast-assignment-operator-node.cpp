//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-assignment-operator-node.h"
#include "../ast-type-nodes/ast-type-assignment-operator-node.h"

std::shared_ptr<ASTNode> ASTAssignmentOperatorNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({ AST_TYPE_NAME_NODE })) {
        return std::make_shared<ASTTypeAssignmentOperatorNode>(this->getLexeme());
    }
    return shared_from_this();
}

ASTNodeType ASTAssignmentOperatorNode::getNodeType() {
    return AST_ASSIGNMENT_OPERATOR_NODE;
}

std::string ASTAssignmentOperatorNode::toString() {
    return "ASSIGNMENT_OPERATOR";
}