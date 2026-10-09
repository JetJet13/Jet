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
// Created by Johny Georges on 2024-03-14.
//

#include "ast-block-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-control-flow-nodes/ast-control-flow-block-node.h"
#include "../ast-class-nodes/ast-class-block-node.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTBlockNode::ASTBlockNode(std::shared_ptr<ASTBlockStartNode> blockStartNode, std::shared_ptr<ASTBlockEndNode> blockEndNode) {
    _blockStartNode = blockStartNode;
    _blockEndNode = blockEndNode;
    _children.push_back(_blockStartNode);
    _children.push_back(_blockEndNode);
    _contents = std::vector<std::shared_ptr<ASTNode>>();
}

ASTBlockNode::ASTBlockNode(std::shared_ptr<ASTBlockStartNode> blockStartNode, std::vector<std::shared_ptr<ASTNode>> contents, std::shared_ptr<ASTBlockEndNode> blockEndNode) {
    _blockStartNode = blockStartNode;
    _blockEndNode = blockEndNode;
    _children.push_back(_blockStartNode);
    _children.push_back(_blockEndNode);
    _contents = std::vector<std::shared_ptr<ASTNode>>();
    for (auto content: contents) {
        _contents.push_back(content);
        _children.insert(_children.end() - 1, content);
    }
}

std::shared_ptr<ASTBlockNode> ASTBlockNode::addContent(std::shared_ptr<ASTNode> content) {
    _contents.push_back(content);
    _children.insert(_children.end() - 1, content);
    return std::dynamic_pointer_cast<ASTBlockNode>(shared_from_this());
}

void ASTBlockNode::hoistTypes(std::vector<ASTNodeType> astNodeTypes) {
    auto newContent = std::vector<std::shared_ptr<ASTNode>>();
    for (auto content: _contents) {
        if (content->isOneOf(astNodeTypes)) {
            newContent.insert(newContent.begin(), content);
        } else {
            newContent.push_back(content);
        }
    }
    _contents = newContent;
}

uint64_t ASTBlockNode::size() {
    return _contents.size();
}

std::vector<std::shared_ptr<ASTNode>>* ASTBlockNode::getContents() {
    return &_contents;
}

std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>* ASTBlockNode::getReturnStatements() {
    return new std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>();
}

std::shared_ptr<ASTNode> ASTBlockNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({AST_TYPE_NODE, AST_FUNCTION_PARAMETER_LIST_NODE, AST_TYPE_PARAMETER_LIST_NODE })) {
        return std::make_shared<ASTFunctionBlockNode>(_blockStartNode, _contents, _blockEndNode);
    }

    if (prevNode && prevNode.value()->isOneOf({AST_CONTROL_FLOW_CONDITION_NODE, AST_ELSE_NODE, AST_FOR_IN_SOURCE_NODE, AST_TRY_NODE, AST_CATCH_NODE, AST_CATCH_ERROR_VARIABLE_NODE, AST_FINALLY_NODE })) {
        return std::make_shared<ASTControlFlowBlockNode>(_blockStartNode, _contents, _blockEndNode);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_CLASS_NAME_NODE, AST_IMPLEMENTS_INTERFACE_LIST_NODE })) {
        return std::make_shared<ASTClassBlockNode>(_blockStartNode, _contents, _blockEndNode);
    }

    return shared_from_this();
}

std::shared_ptr<Position> ASTBlockNode::getStartPosition() {
    return _blockStartNode->getStartPosition();
}

std::shared_ptr<Position> ASTBlockNode::getEndPosition() {
    return _blockEndNode->getEndPosition();
}

ASTNodeType ASTBlockNode::getNodeType() {
    return AST_BLOCK_NODE;
}

std::string ASTBlockNode::toString() {
    return "BLOCK";
}

bool ASTBlockNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTBlockNode>(other);
    for (uint64_t i = 0; i < _contents.size(); ++i) {
        if (!_contents[i]->isSameAs(otherNode->getContents()->at(i))) {
            return false;
        }
    }
    return true;
}

void ASTBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _blockStartNode->print();
    for (auto content : _contents) {
        content->print();
    }
    _blockEndNode->print();
    Logger::log("----------");
}

std::string ASTBlockNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_blockStartNode);

    for (auto content : _contents) {
        sourceCodeBuilder.add(content);
    }

    sourceCodeBuilder.add(_blockEndNode);

    return sourceCodeBuilder.build();
}