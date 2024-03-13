//
// Created by Johny Georges on 2024-03-11.
//

#include "ast-array-node.h"
#include "../ast-expression-nodes/ast-array-expression-node.h"
#include "ast-array-access-node.h"

ASTArrayNode::ASTArrayNode() {
    _elements = new std::vector<ASTExpressionNode*>();
}

ASTArrayNode::ASTArrayNode(std::vector<ASTExpressionNode*> elements) {
    _elements = new std::vector<ASTExpressionNode*>();
    for (auto element: elements) {
        _elements->push_back(element);
    }
}

ASTArrayNode* ASTArrayNode::addElement(ASTExpressionNode* element) {
    _elements->push_back(element);
    return this;
}

unsigned long ASTArrayNode::getSize() {

}

std::optional<ASTExpressionNode*> ASTArrayNode::getFirstElement() {
    if (_elements->at(0)) {
        return _elements->at(0);
    }
    return {};
}

std::vector<ASTExpressionNode*>* ASTArrayNode::getElements() {
    return _elements;
}

ASTNodeType ASTArrayNode::getNodeType() {
    return AST_ARRAY_NODE;
}

std::string ASTArrayNode::toString() {
    return "ARRAY_BASE";
}