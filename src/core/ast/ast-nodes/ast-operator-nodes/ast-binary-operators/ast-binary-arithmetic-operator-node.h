//
// Created by Johny Georges on 2024-02-07.
//

#ifndef JETLANG_AST_BINARY_ARITHMETIC_OPERATOR_NODE_H
#define JETLANG_AST_BINARY_ARITHMETIC_OPERATOR_NODE_H

#include "../../ast-node.h"
#include "../../../../lexeme/lexeme.h"

class ASTBinaryArithmeticOperatorNode : public ASTNode {
private:
    Lexeme* _lexeme;
    unsigned int _priority;
    unsigned int determinePriority(Lexeme* lexeme);
public:
    explicit ASTBinaryArithmeticOperatorNode(Lexeme* lexeme);
    Lexeme* getOperator();
    unsigned int getPriority() const;
    bool isHigherOrEqualPriorityThan(ASTBinaryArithmeticOperatorNode* other) const;
    bool isPlus();
    bool isMinus();
    bool isMultiply();
    bool isDivide();
    bool isModulo();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_BINARY_ARITHMETIC_OPERATOR_NODE_H
