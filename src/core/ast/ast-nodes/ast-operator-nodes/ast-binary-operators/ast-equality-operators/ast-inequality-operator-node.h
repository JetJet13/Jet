//
// Created by Johny Georges on 2024-02-22.
//

#ifndef JETLANG_AST_INEQUALITY_OPERATOR_NODE_H
#define JETLANG_AST_INEQUALITY_OPERATOR_NODE_H

#include "../../../ast-node.h"
#include "../../../../../lexeme/lexeme.h"
#include "../ast-binary-operator-node.h"

class ASTInequalityOperatorNode : public ASTBinaryOperatorNode {
private:
    Lexeme* _inequality;
public:
    ASTInequalityOperatorNode(Lexeme* lexeme);
    ASTNodeType getNodeType() override;
};

#endif //JETLANG_AST_INEQUALITY_OPERATOR_NODE_H
