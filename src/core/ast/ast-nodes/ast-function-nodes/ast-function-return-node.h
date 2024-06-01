//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_AST_FUNCTION_RETURN_NODE_H
#define JETLANG_AST_FUNCTION_RETURN_NODE_H

#include <string>
#include "../ast-symbol-node.h"
#include "../../types/ast-node-type.h"

class ASTFunctionReturnNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_FUNCTION_RETURN_NODE_H
