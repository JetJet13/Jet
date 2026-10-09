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
// Created by Johny Georges on 2024-03-28.
//

#include "ast-control-flow-block-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTControlFlowBlockNode::ASTControlFlowBlockNode(std::shared_ptr<ASTBlockStartNode> blockStartNode, std::vector<std::shared_ptr<ASTNode>> contents, std::shared_ptr<ASTBlockEndNode> blockEndNode) {
    _blockStartNode = blockStartNode;
    _blockEndNode = blockEndNode;
    _contents = std::vector<std::shared_ptr<ASTNode>>();
    _returnStatements = std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>();
    _children.push_back(_blockStartNode);
    for (auto content: contents) {
        _contents.push_back(content);
        _children.push_back(content);
        if (content->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
            _returnStatements.push_back(std::dynamic_pointer_cast<ASTFunctionReturnExpressionNode>(content));
        } else if (content->isScopedBlockNode()) {
            auto scopeBlockNodeReturnStatements = (std::dynamic_pointer_cast<ASTScopedBlockNode>(content))->getReturnStatements();
            _returnStatements.insert(
                    _returnStatements.end(),
                    scopeBlockNodeReturnStatements->begin(),
                    scopeBlockNodeReturnStatements->end()
            );
        }
    }
    _children.push_back(_blockEndNode);
}

std::vector<std::shared_ptr<ASTNode>>* ASTControlFlowBlockNode::getContents() {
    return &_contents;
}

std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>* ASTControlFlowBlockNode::getReturnStatements() {
    return &_returnStatements;
}

bool ASTControlFlowBlockNode::hasReturnExpression() {
   return !_returnStatements.empty();
}

std::shared_ptr<Position> ASTControlFlowBlockNode::getStartPosition() {
    return _blockStartNode->getStartPosition();
}

std::shared_ptr<Position> ASTControlFlowBlockNode::getEndPosition() {
    return _blockEndNode->getEndPosition();
}

ASTNodeType ASTControlFlowBlockNode::getNodeType() {
    return AST_CONTROL_FLOW_BLOCK_NODE;
}

std::string ASTControlFlowBlockNode::toString() {
    return "CONTROL_FLOW_BLOCK";
}

bool ASTControlFlowBlockNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTControlFlowBlockNode>(other);
    for (uint64_t i = 0; i < _contents.size(); ++i) {
        if (!_contents[i]->isSameAs(otherNode->getContents()->at(i))) {
            return false;
        }
    }
    return true;
}

void ASTControlFlowBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto content : _contents) {
        content->print();
    }
    Logger::log("----------");
}

std::string ASTControlFlowBlockNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_blockStartNode);

    for (auto content : _contents) {
        sourceCodeBuilder.add(content);
    }

    sourceCodeBuilder.add(_blockEndNode);
    return sourceCodeBuilder.build();
}