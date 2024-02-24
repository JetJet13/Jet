//
// Created by Johny Georges on 2024-02-22.
//

#ifndef JETLANG_AST_LESS_THAN_OPERATOR_NODE_H
#define JETLANG_AST_LESS_THAN_OPERATOR_NODE_H

#include "../ast-binary-operator-node.h"
#include "../../../../../lexeme/lexeme.h"

class ASTLessThanOperatorNode : public ASTBinaryOperatorNode {
private:
    Lexeme* _lessThan;
public:
    ASTLessThanOperatorNode(Lexeme* lexeme);
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_LESS_THAN_OPERATOR_NODE_H
