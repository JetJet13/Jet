//
// Created by Johny Georges on 2024-04-01.
//

#ifndef JETLANG_AST_CATCH_ERROR_VARIABLE_NODE_H
#define JETLANG_AST_CATCH_ERROR_VARIABLE_NODE_H

#include <string>
#include "../../ast-symbol-node.h"

class ASTCatchErrorVariableNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CATCH_ERROR_VARIABLE_NODE_H
