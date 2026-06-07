//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-block-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-control-flow-nodes/ast-control-flow-block-node.h"
#include "../ast-class-nodes/ast-class-block-node.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTBlockNode::ASTBlockNode(ASTBlockStartNode* blockStartNode, ASTBlockEndNode* blockEndNode) {
    _blockStartNode = blockStartNode;
    _blockEndNode = blockEndNode;
    _children.push_back(_blockStartNode);
    _children.push_back(_blockEndNode);
    _contents = std::vector<ASTNode*>();
}

ASTBlockNode::ASTBlockNode(ASTBlockStartNode* blockStartNode, std::vector<ASTNode*> contents, ASTBlockEndNode* blockEndNode) {
    _blockStartNode = blockStartNode;
    _blockEndNode = blockEndNode;
    _children.push_back(_blockStartNode);
    _children.push_back(_blockEndNode);
    _contents = std::vector<ASTNode*>();
    for (auto content: contents) {
        this->addContent(content);
    }
}

ASTBlockNode* ASTBlockNode::addContent(ASTNode* content) {
    _contents.push_back(content);
    _children.insert(_children.end() - 1, content);
    return this;
}

void ASTBlockNode::hoistTypes(std::vector<ASTNodeType> astNodeTypes) {
    auto newContent = std::vector<ASTNode*>();
    for (auto content: _contents) {
        if (content->isOneOf(astNodeTypes)) {
            newContent.insert(newContent.begin(), content);
        } else {
            newContent.push_back(content);
        }
    }
    _contents = newContent;
}

unsigned long ASTBlockNode::size() {
    return _contents.size();
}

std::vector<ASTNode*>* ASTBlockNode::getContents() {
    return &_contents;
}

std::vector<ASTFunctionReturnExpressionNode*>* ASTBlockNode::getReturnStatements() {
    return new std::vector<ASTFunctionReturnExpressionNode*>();
}

ASTNode * ASTBlockNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode,
                                             SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({AST_TYPE_NODE, AST_FUNCTION_PARAMETER_LIST_NODE, AST_PROCEDURE_PARAMETER_LIST_NODE, AST_TYPE_PARAMETER_LIST_NODE })) {
        return new ASTFunctionBlockNode(_blockStartNode, _contents, _blockEndNode);
    }

    if (prevNode && prevNode.value()->isOneOf({AST_CONTROL_FLOW_CONDITION_NODE, AST_ELSE_NODE, AST_FOR_IN_SOURCE_NODE, AST_TRY_NODE, AST_CATCH_NODE, AST_CATCH_ERROR_VARIABLE_NODE, AST_FINALLY_NODE })) {
        return new ASTControlFlowBlockNode(_blockStartNode, _contents, _blockEndNode);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_CLASS_NAME_NODE, AST_IMPLEMENTS_INTERFACE_LIST_NODE })) {
        return new ASTClassBlockNode(_blockStartNode, _contents, _blockEndNode);
    }

    return this;
}

Position* ASTBlockNode::getStartPosition() {
    return _blockStartNode->getStartPosition();
}

Position* ASTBlockNode::getEndPosition() {
    return _blockEndNode->getEndPosition();
}

ASTNodeType ASTBlockNode::getNodeType() {
    return AST_BLOCK_NODE;
}

std::string ASTBlockNode::toString() {
    return "BLOCK";
}

bool ASTBlockNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTBlockNode*)other;
    for (unsigned long i = 0; i < _contents.size(); ++i) {
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