//
// Created by Johny Georges on 2025-10-16.
//

#include "ast-tuple-access-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTupleAccessAssignmentNode::ASTTupleAccessAssignmentNode(std::shared_ptr<ASTTupleAccessExpressionNode> tupleAccessExpression, std::shared_ptr<ASTAssignmentOperatorNode> assignmentOperator) {
    _tupleAccessExpression = tupleAccessExpression;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_tupleAccessExpression);
    _children.push_back(_assignmentOperator);
}

std::shared_ptr<ASTTupleAccessExpressionNode> ASTTupleAccessAssignmentNode::getTupleAccess() {
    return _tupleAccessExpression;
}

TypeSignature* ASTTupleAccessAssignmentNode::getTypeSignature() {
    return _tupleAccessExpression->getTypeSignature();
}

Position* ASTTupleAccessAssignmentNode::getStartPosition() {
    return _tupleAccessExpression->getStartPosition();
}

Position* ASTTupleAccessAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTTupleAccessAssignmentNode::getNodeType() {
    return AST_TUPLE_ACCESS_ASSIGNMENT_NODE;
}

std::string ASTTupleAccessAssignmentNode::toString() {
    return "TUPLE_ACCESS_ASSIGNMENT";
}

bool ASTTupleAccessAssignmentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTupleAccessAssignmentNode>(other);
    return this->getTupleAccess()->isSameAs(otherNode->getTupleAccess());
}

void ASTTupleAccessAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _tupleAccessExpression->print();
    Logger::log("----------");
}

std::string ASTTupleAccessAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tupleAccessExpression)
            ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}