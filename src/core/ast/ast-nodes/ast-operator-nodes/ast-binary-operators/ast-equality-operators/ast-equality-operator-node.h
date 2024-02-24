//
// Created by Johny Georges on 2024-02-22.
//

#ifndef JETLANG_AST_EQUALITY_OPERATOR_NODE_H
#define JETLANG_AST_EQUALITY_OPERATOR_NODE_H

#include "../../../ast-node.h"
#include "../../../../../lexeme/lexeme.h"
#include "../ast-binary-operator-node.h"

class ASTEqualityOperatorNode : public ASTBinaryOperatorNode {
private:
    Lexeme* _equality;
public:
    ASTEqualityOperatorNode(Lexeme* lexeme);
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_EQUALITY_OPERATOR_NODE_H
