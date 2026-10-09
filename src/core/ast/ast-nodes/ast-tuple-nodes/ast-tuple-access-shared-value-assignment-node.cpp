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
// Created by Johny Georges on 2026-06-26.
//

#include "ast-tuple-access-shared-value-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTupleAccessSharedValueAssignmentNode::ASTTupleAccessSharedValueAssignmentNode(std::shared_ptr<ASTTupleAccessExpressionNode> tupleAccessExpression, std::shared_ptr<ASTSharedValueAssignmentOperatorNode> assignmentOperator) {
    _tupleAccessExpression = tupleAccessExpression;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_tupleAccessExpression);
    _children.push_back(_assignmentOperator);
}

std::shared_ptr<ASTTupleAccessExpressionNode> ASTTupleAccessSharedValueAssignmentNode::getTupleAccess() {
    return _tupleAccessExpression;
}

std::shared_ptr<TypeSignature> ASTTupleAccessSharedValueAssignmentNode::getTypeSignature() {
    return _tupleAccessExpression->getTypeSignature();
}

std::shared_ptr<Position> ASTTupleAccessSharedValueAssignmentNode::getStartPosition() {
    return _tupleAccessExpression->getStartPosition();
}

std::shared_ptr<Position> ASTTupleAccessSharedValueAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTTupleAccessSharedValueAssignmentNode::getNodeType() {
    return AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE;
}

std::string ASTTupleAccessSharedValueAssignmentNode::toString() {
    return "TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT";
}

bool ASTTupleAccessSharedValueAssignmentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTupleAccessSharedValueAssignmentNode>(other);
    return this->getTupleAccess()->isSameAs(otherNode->getTupleAccess());
}

void ASTTupleAccessSharedValueAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _tupleAccessExpression->print();
    Logger::log("----------");
}

std::string ASTTupleAccessSharedValueAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tupleAccessExpression)
            ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}