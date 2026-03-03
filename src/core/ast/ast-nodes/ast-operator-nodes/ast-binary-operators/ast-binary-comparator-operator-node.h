//
// Created by Johny Georges on 2026-03-02.
//

#ifndef JETLANG_AST_BINARY_COMPARATOR_OPERATOR_NODE_H
#define JETLANG_AST_BINARY_COMPARATOR_OPERATOR_NODE_H

#include "../../ast-node.h"
#include "../../../../lexeme/lexeme.h"

class ASTBinaryComparatorOperatorNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    explicit ASTBinaryComparatorOperatorNode(Lexeme* lexeme);
    Lexeme* getOperator();
    bool isEqual();
    bool isNotEqual();
    bool isGreaterThan();
    bool isLessThan();
    bool isGreaterThanOrEqual();
    bool isLessThanOrEqual();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_BINARY_COMPARATOR_OPERATOR_NODE_H
