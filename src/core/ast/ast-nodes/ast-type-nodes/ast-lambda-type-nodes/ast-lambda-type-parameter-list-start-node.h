//
// Created by Johny Georges on 2025-07-09.
//

#ifndef JETLANG_AST_LAMBDA_TYPE_PARAMETER_LIST_START_NODE_H
#define JETLANG_AST_LAMBDA_TYPE_PARAMETER_LIST_START_NODE_H

#include <string>
#include "../../ast-node.h"
#include "../../../../lexeme/lexeme.h"
#include "../../ast-symbol-node.h"

class ASTLambdaTypeParameterListStartNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_LAMBDA_TYPE_PARAMETER_LIST_START_NODE_H
