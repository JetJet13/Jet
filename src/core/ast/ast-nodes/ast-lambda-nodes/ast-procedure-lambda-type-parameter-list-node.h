//
// Created by Johny Georges on 2024-04-06.
//

#ifndef JETLANG_AST_PROCEDURE_LAMBDA_TYPE_PARAMETER_LIST_NODE_H
#define JETLANG_AST_PROCEDURE_LAMBDA_TYPE_PARAMETER_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-type-nodes/ast-type-parameter-list-node.h"

class ASTProcedureLambdaTypeParameterListNode : public ASTTypeParameterListNode {
    using ASTTypeParameterListNode::ASTTypeParameterListNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_PROCEDURE_LAMBDA_TYPE_PARAMETER_LIST_NODE_H
