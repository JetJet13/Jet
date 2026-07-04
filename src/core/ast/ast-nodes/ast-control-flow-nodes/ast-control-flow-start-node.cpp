//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-control-flow-start-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-block-nodes/ast-block-start-node.h"

std::shared_ptr<ASTNode> ASTControlFlowStartNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (mode != SA_CONTROL_FLOW_MODE) {
        return std::make_shared<ASTBlockStartNode>(_lexeme);
    }
    return shared_from_this();
}

ASTNodeType ASTControlFlowStartNode::getNodeType() {
    return AST_CONTROL_FLOW_START_NODE;
}

std::string ASTControlFlowStartNode::toString() {
    return "CONTROL_FLOW_START";
}