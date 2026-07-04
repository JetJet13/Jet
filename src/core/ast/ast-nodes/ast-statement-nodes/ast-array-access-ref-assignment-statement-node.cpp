//
// Created by Johny Georges on 2026-06-26.
//

#include "ast-array-access-ref-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTArrayAccessRefAssignmentStatementNode::ASTArrayAccessRefAssignmentStatementNode(std::shared_ptr<ASTArrayAccessRefAssignmentNode> arrayAccessAssignment, std::shared_ptr<ASTExpressionNode> expression) {
    _arrayAccessAssignment = arrayAccessAssignment;
    _expression = expression;
    _children.push_back(_arrayAccessAssignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTArrayAccessRefAssignmentNode> ASTArrayAccessRefAssignmentStatementNode::getArrayAccessAssignment() {
    return _arrayAccessAssignment;
}

std::shared_ptr<ASTExpressionNode> ASTArrayAccessRefAssignmentStatementNode::getExpression() {
    return _expression;
}

Position* ASTArrayAccessRefAssignmentStatementNode::getStartPosition() {
    return _arrayAccessAssignment->getStartPosition();
}

Position* ASTArrayAccessRefAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTArrayAccessRefAssignmentStatementNode::getNodeType() {
    return AST_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTArrayAccessRefAssignmentStatementNode::toString() {
    return "ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT";
}

bool ASTArrayAccessRefAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTArrayAccessRefAssignmentStatementNode>(other);
    return this->getArrayAccessAssignment()->isSameAs(otherNode->getArrayAccessAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTArrayAccessRefAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _arrayAccessAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTArrayAccessRefAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_arrayAccessAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}