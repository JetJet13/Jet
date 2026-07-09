//
// Created by Johny Georges on 2026-06-26.
//

#include "ast-module-access-ref-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTModuleAccessRefAssignmentStatementNode::ASTModuleAccessRefAssignmentStatementNode(std::shared_ptr<ASTModuleAccessRefAssignmentNode> moduleAccessAssignment, std::shared_ptr<ASTExpressionNode> expression) {
    _moduleAccessAssignment = moduleAccessAssignment;
    _expression = expression;
    _children.push_back(_moduleAccessAssignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTModuleAccessRefAssignmentNode> ASTModuleAccessRefAssignmentStatementNode::getModuleAccessAssignment() {
    return _moduleAccessAssignment;
}

std::shared_ptr<ASTExpressionNode> ASTModuleAccessRefAssignmentStatementNode::getExpression() {
    return _expression;
}

std::shared_ptr<Position> ASTModuleAccessRefAssignmentStatementNode::getStartPosition() {
    return _moduleAccessAssignment->getStartPosition();
}

std::shared_ptr<Position> ASTModuleAccessRefAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTModuleAccessRefAssignmentStatementNode::getNodeType() {
    return AST_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTModuleAccessRefAssignmentStatementNode::toString() {
    return "MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT";
}

bool ASTModuleAccessRefAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleAccessRefAssignmentStatementNode>(other);
    return this->getModuleAccessAssignment()->isSameAs(otherNode->getModuleAccessAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTModuleAccessRefAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleAccessAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTModuleAccessRefAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleAccessAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}