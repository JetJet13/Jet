//
// Created by Johny Georges on 2024-02-07.
//

#ifndef JETLANG_AST_BINARY_ARITHMETIC_OPERATOR_NODE_H
#define JETLANG_AST_BINARY_ARITHMETIC_OPERATOR_NODE_H

#include "../../ast-node.h"
#include "../../../../lexeme/lexeme.h"

class ASTBinaryArithmeticOperatorNode : public ASTNode {
private:
    std::shared_ptr<Lexeme> _lexeme;
    unsigned int _priority;
    unsigned int determinePriority(std::shared_ptr<Lexeme> lexeme);
public:
    explicit ASTBinaryArithmeticOperatorNode(std::shared_ptr<Lexeme> lexeme);
    std::shared_ptr<Lexeme> getOperator();
    unsigned int getPriority() const;
    bool isHigherOrEqualPriorityThan(std::shared_ptr<ASTBinaryArithmeticOperatorNode> other) const;
    bool isPlus();
    bool isMinus();
    bool isMultiply();
    bool isDivide();
    bool isModulo();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_BINARY_ARITHMETIC_OPERATOR_NODE_H
