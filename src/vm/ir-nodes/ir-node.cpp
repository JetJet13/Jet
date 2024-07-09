//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-node.h"


bool IRNode::is(IRNodeType irNodeType) {
    return this->getNodeType() == irNodeType;
}
