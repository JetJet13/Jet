//
// Created by Johny Georges on 2024-05-20.
//

#ifndef JETLANG_AST_LITERAL_NODE_VALUE_ASSIGNOR_H
#define JETLANG_AST_LITERAL_NODE_VALUE_ASSIGNOR_H

#include "../../../token/token-table.h"
#include "../../../ast/ast-nodes/ast-literal-nodes/ast-literal-node.h"

class ASTLiteralNodeValueAssignor {
public:
    void static assignValue(ASTNode* node, std::shared_ptr<TokenTable> tokenTable);
};

#endif //JETLANG_AST_LITERAL_NODE_VALUE_ASSIGNOR_H
