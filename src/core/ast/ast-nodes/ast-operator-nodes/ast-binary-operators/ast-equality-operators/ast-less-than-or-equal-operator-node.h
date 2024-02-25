//
// Created by Johny Georges on 2024-02-22.
//

#ifndef JETLANG_AST_LESS_THAN_OR_EQUAL_OPERATOR_NODE_H
#define JETLANG_AST_LESS_THAN_OR_EQUAL_OPERATOR_NODE_H

#include "../ast-binary-operator-node.h"
#include "../../../../../lexeme/lexeme.h"

class ASTLessThanOrEqualOperatorNode : public ASTBinaryOperatorNode {
private:
    Lexeme* _lessThanOrEqual;
public:
    ASTLessThanOrEqualOperatorNode(Lexeme* lexeme);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isEqual(ASTNode* other) override;
};

#endif //JETLANG_AST_LESS_THAN_OR_EQUAL_OPERATOR_NODE_H
