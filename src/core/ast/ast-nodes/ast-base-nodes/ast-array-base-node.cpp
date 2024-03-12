//
// Created by Johny Georges on 2024-03-11.
//

#include "ast-array-base-node.h"
#include "../ast-expression-nodes/ast-array-expression-node.h"
#include "../ast-array-nodes/ast-array-access-node.h"

ASTArrayBaseNode::ASTArrayBaseNode() {
    _elements = new std::vector<ASTExpressionNode*>();
}

ASTArrayBaseNode::ASTArrayBaseNode(std::vector<ASTExpressionNode*> elements) {
    _elements = new std::vector<ASTExpressionNode*>();
    for (auto element: elements) {
        _elements->push_back(element);
    }
}

ASTArrayBaseNode* ASTArrayBaseNode::addElement(ASTExpressionNode* element) {
    _elements->push_back(element);
    return this;
}

unsigned long ASTArrayBaseNode::getSize() {

}

std::optional<ASTExpressionNode*> ASTArrayBaseNode::getFirstElement() {
    if (_elements->at(0)) {
        return _elements->at(0);
    }
    return {};
}

std::vector<ASTExpressionNode*>* ASTArrayBaseNode::getElements() {
    return _elements;
}

ASTNodeType ASTArrayBaseNode::getNodeType() {
    return AST_ARRAY_BASE_NODE;
}

std::string ASTArrayBaseNode::toString() {
    return "ARRAY_BASE";
}