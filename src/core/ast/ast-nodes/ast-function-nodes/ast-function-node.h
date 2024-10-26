//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_AST_FUNCTION_NODE_H
#define JETLANG_AST_FUNCTION_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-symbol-node.h"
#include "../../types/ast-node-type.h"
// create a new 'function definition' ast-node to get exports to work
// function keyword + function name + function parameters + function return type
class ASTFunctionNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_FUNCTION_NODE_H
