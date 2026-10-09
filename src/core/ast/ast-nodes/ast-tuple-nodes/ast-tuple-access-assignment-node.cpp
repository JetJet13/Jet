// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

std::shared_ptr<TypeSignature> ASTTupleAccessAssignmentNode::getTypeSignature() {
    return _tupleAccessExpression->getTypeSignature();
}

std::shared_ptr<Position> ASTTupleAccessAssignmentNode::getStartPosition() {
    return _tupleAccessExpression->getStartPosition();
}

std::shared_ptr<Position> ASTTupleAccessAssignmentNode::getEndPosition() {
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