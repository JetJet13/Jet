//
// Created by Johny Georges on 2024-02-07.
//

#ifndef JETLANG_AST_BINARY_OPERATOR_NODE_H
#define JETLANG_AST_BINARY_OPERATOR_NODE_H

#include "../../ast-symbol-node.h"
#include "../../../../lexeme/lexeme.h"

class ASTBinaryOperatorNode : public ASTSymbolNode {
private:
    unsigned int determinePriority(Lexeme* lexeme);
public:
    ASTBinaryOperatorNode(Lexeme* lexeme);
    Lexeme* getOperator();
    bool isPlus();
    bool isMinus();
    bool isMultiply();
    bool isDivide();
    bool isModulo();
    bool isEqual();
    bool isNotEqual();
    bool isGreaterThan();
    bool isLessThan();
    bool isGreaterThanOrEqual();
    bool isLessThanOrEqual();
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_BINARY_OPERATOR_NODE_H
