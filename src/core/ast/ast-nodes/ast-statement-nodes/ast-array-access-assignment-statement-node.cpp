//
// Created by Johny Georges on 2025-02-17.
//

#include "ast-array-access-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTArrayAccessAssignmentStatementNode::ASTArrayAccessAssignmentStatementNode(std::shared_ptr<ASTArrayAccessAssignmentNode> arrayAccessAssignment, std::shared_ptr<ASTExpressionNode> expression) {
    _arrayAccessAssignment = arrayAccessAssignment;
    _expression = expression;
    _children.push_back(_arrayAccessAssignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTArrayAccessAssignmentNode> ASTArrayAccessAssignmentStatementNode::getArrayAccessAssignment() {
    return _arrayAccessAssignment;
}

std::shared_ptr<ASTExpressionNode> ASTArrayAccessAssignmentStatementNode::getExpression() {
    return _expression;
}

std::shared_ptr<Position> ASTArrayAccessAssignmentStatementNode::getStartPosition() {
    return _arrayAccessAssignment->getStartPosition();
}

std::shared_ptr<Position> ASTArrayAccessAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTArrayAccessAssignmentStatementNode::getNodeType() {
    return AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTArrayAccessAssignmentStatementNode::toString() {
    return "ARRAY_ACCESS_ASSIGNMENT_STATEMENT";
}

bool ASTArrayAccessAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTArrayAccessAssignmentStatementNode>(other);
    return this->getArrayAccessAssignment()->isSameAs(otherNode->getArrayAccessAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTArrayAccessAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _arrayAccessAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTArrayAccessAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_arrayAccessAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}