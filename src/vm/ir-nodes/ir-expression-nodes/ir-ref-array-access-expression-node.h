//
// Created by Johny Georges on 2025-06-21.
//

#ifndef JETLANG_IR_REF_ARRAY_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_REF_ARRAY_ACCESS_EXPRESSION_NODE_H

#include "ir-array-access-expression-node.h"

class IRRefArrayAccessExpressionNode : public IRArrayAccessExpressionNode {
    using IRArrayAccessExpressionNode::IRArrayAccessExpressionNode;
public:
    IRNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_IR_REF_ARRAY_ACCESS_EXPRESSION_NODE_H
