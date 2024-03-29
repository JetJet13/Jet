//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTForStatementNode::ASTForStatementNode(ASTForVariableNode* variable, ASTForSourceNode* source, ASTControlFlowBlockNode* block) {
    _variable = variable;
    _source = source;
    _block = block;
}

ASTForVariableNode* ASTForStatementNode::getVariable() {
    return _variable;
}

ASTForSourceNode* ASTForStatementNode::getSource() {
    return _source;
}

ASTControlFlowBlockNode* ASTForStatementNode::getBlock() {
    return _block;
}

ASTNodeType ASTForStatementNode::getNodeType() {
    return AST_FOR_STATEMENT_NODE;
}

std::string ASTForStatementNode::toString() {
    return "FOR_STATEMENT";
}

bool ASTForStatementNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTForStatementNode*)other;

    return  this->getVariable()->isSameAs(otherNode->getVariable()) &&
            this->getSource()->isSameAs(otherNode->getSource());
}

void ASTForStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _variable->print();
    _source->print();
    Logger::log("----------");
}