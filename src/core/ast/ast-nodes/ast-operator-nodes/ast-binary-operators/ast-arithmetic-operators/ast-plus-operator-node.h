//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_AST_PLUS_OPERATOR_NODE_H
#define JETLANG_AST_PLUS_OPERATOR_NODE_H

#include "../../../ast-node.h"
#include "../../../../../lexeme/lexeme.h"
#include "../ast-binary-operator-node.h"

class ASTPlusOperatorNode : public ASTBinaryOperatorNode {
private:
    Lexeme* _plusOperator;
public:
    ASTPlusOperatorNode(Lexeme* plusOperator);
    ASTNodeType getNodeType() override;
    std::string toString() override;
};


#endif //JETLANG_AST_PLUS_OPERATOR_NODE_H
