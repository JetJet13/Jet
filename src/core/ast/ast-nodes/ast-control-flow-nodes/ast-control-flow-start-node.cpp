//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-control-flow-start-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-block-nodes/ast-block-start-node.h"

ASTControlFlowStartNode::ASTControlFlowStartNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTControlFlowStartNode::getLexeme() {
    return _lexeme;
}

ASTNode* ASTControlFlowStartNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    if (mode != SA_CONTROL_FLOW_MODE) {
        return new ASTBlockStartNode(_lexeme);
    }
    return this;
}

ASTNodeType ASTControlFlowStartNode::getNodeType() {
    return AST_CONTROL_FLOW_START_NODE;
}

std::string ASTControlFlowStartNode::toString() {
    return "CONTROL_FLOW_START";
}

bool ASTControlFlowStartNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTControlFlowStartNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTControlFlowStartNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}