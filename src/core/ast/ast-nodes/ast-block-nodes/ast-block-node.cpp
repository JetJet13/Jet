//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-block-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-control-flow-nodes/ast-control-flow-block-node.h"
#include "../ast-class-nodes/ast-class-block-node.h"

ASTBlockNode::ASTBlockNode() {
    _contents = std::vector<ASTNode*>();
}

ASTBlockNode::ASTBlockNode(std::vector<ASTNode*> contents) {
    _contents = std::vector<ASTNode*>();
    for (auto content: contents) {
        this->addContent(content);
    }
}

ASTBlockNode* ASTBlockNode::addContent(ASTNode* content) {
    _contents.push_back(content);
    _children.push_back(content);
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

ASTNode * ASTBlockNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode,
                                             SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({AST_TYPE_NODE, AST_FUNCTION_PARAMETER_LIST_NODE, AST_TYPE_PARAMETER_LIST_NODE })) {
        return new ASTFunctionBlockNode(_contents);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_CONTROL_FLOW_CONDITION_NODE, AST_ELSE_NODE, AST_FOR_SOURCE_NODE, AST_TRY_NODE, AST_CATCH_NODE, AST_CATCH_ERROR_VARIABLE_NODE, AST_FINALLY_NODE })) {
        return new ASTControlFlowBlockNode(_contents);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_CLASS_NAME_NODE })) {
        return new ASTClassBlockNode(_contents);
    }

    return this;
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
    for (int i = 0; i < _contents.size(); ++i) {
        if (!_contents[i]->isSameAs(otherNode->getContents()->at(i))) {
            return false;
        }
    }
    return true;
}


void ASTBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto content : _contents) {
        content->print();
    }
    Logger::log("----------");
}