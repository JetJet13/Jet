//
// Created by Johny Georges on 2026-04-02.
//

#include "ast-module-access-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTModuleAccessAssignmentStatementNode::ASTModuleAccessAssignmentStatementNode(std::shared_ptr<ASTModuleAccessAssignmentNode> moduleAccessAssignment, std::shared_ptr<ASTExpressionNode> expression) {
    _moduleAccessAssignment = moduleAccessAssignment;
    _expression = expression;
    _children.push_back(_moduleAccessAssignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTModuleAccessAssignmentNode> ASTModuleAccessAssignmentStatementNode::getModuleAccessAssignment() {
    return _moduleAccessAssignment;
}

std::shared_ptr<ASTExpressionNode> ASTModuleAccessAssignmentStatementNode::getExpression() {
    return _expression;
}

Position* ASTModuleAccessAssignmentStatementNode::getStartPosition() {
    return _moduleAccessAssignment->getStartPosition();
}

Position* ASTModuleAccessAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTModuleAccessAssignmentStatementNode::getNodeType() {
    return AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTModuleAccessAssignmentStatementNode::toString() {
    return "MODULE_ACCESS_ASSIGNMENT_STATEMENT";
}

bool ASTModuleAccessAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleAccessAssignmentStatementNode>(other);
    return this->getModuleAccessAssignment()->isSameAs(otherNode->getModuleAccessAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTModuleAccessAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleAccessAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTModuleAccessAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleAccessAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}