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
// Created by Johny Georges on 2024-04-01.
//

#include "ast-catch-block-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTCatchBlockNode::ASTCatchBlockNode(std::shared_ptr<ASTCatchNode> catchKeyword, std::shared_ptr<ASTControlFlowBlockNode> block, std::optional<std::shared_ptr<ASTCatchErrorVariableNode>> errorVariable) {
    _catchKeyword = catchKeyword;
    _block = block;
    _errorVariable = errorVariable;
    _children.push_back(_catchKeyword);
    _children.push_back(_block);
    if (_errorVariable) {
        _children.push_back(_errorVariable.value());
    }
}

std::shared_ptr<ASTControlFlowBlockNode> ASTCatchBlockNode::getBlock() {
    return _block;
}

std::optional<std::shared_ptr<ASTCatchErrorVariableNode>> ASTCatchBlockNode::getErrorVariable() {
    return _errorVariable;
}

std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>* ASTCatchBlockNode::getReturnStatements() {
    return _block->getReturnStatements();
}

std::shared_ptr<Position> ASTCatchBlockNode::getStartPosition() {
    return _catchKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTCatchBlockNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTCatchBlockNode::getNodeType() {
    return AST_CATCH_BLOCK_NODE;
}

std::string ASTCatchBlockNode::toString() {
    return "CATCH_BLOCK";
}

bool ASTCatchBlockNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTCatchBlockNode>(other);

    if (!_errorVariable.has_value() && otherNode->getErrorVariable().has_value() ||
        _errorVariable.has_value() && !otherNode->getErrorVariable().has_value()) {
        return false;
    }

    if (_errorVariable.has_value() && otherNode->getErrorVariable().has_value() &&
        !_errorVariable.value()->isSameAs(otherNode->getErrorVariable().value())) {
        return false;
    }

    return this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTCatchBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    if (_errorVariable) {
        _errorVariable.value()->print();
    }
    _block->print();
    Logger::log("----------");
}

std::string ASTCatchBlockNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_catchKeyword);
    if (_errorVariable) {
        sourceCodeBuilder.add(_errorVariable.value());
    }
    sourceCodeBuilder.add(_block);
    return sourceCodeBuilder.build();
}