//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-node.h"


bool IRNode::is(IRNodeType irNodeType) {
    return this->getNodeType() == irNodeType;
}

bool IRNode::isOneOf(std::vector<IRNodeType> irNodeTypes) {
    return std::find(
            irNodeTypes.begin(),
            irNodeTypes.end(),
            this->getNodeType()) != irNodeTypes.end();
}

bool IRNode::isDeclaration() {
    return false;
}

bool IRNode::isExpression() {
    return false;
}

bool IRNode::isTypeDeclaration() {
    return false;
}


bool IRNode::isStatement() {
    return false;
}
