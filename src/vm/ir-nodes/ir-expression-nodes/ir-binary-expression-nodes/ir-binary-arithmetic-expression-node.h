//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_BINARY_ARITHMETIC_EXPRESSION_NODE_H
#define JETLANG_IR_BINARY_ARITHMETIC_EXPRESSION_NODE_H

#include <llvm/IR/InstrTypes.h>
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"
#include "ir-binary-expression-node.h"
#include "../../ir-binary-operator-node.h"

class IRBinaryArithmeticExpressionNode : public IRBinaryExpressionNode {
private:
    ASTBinaryExpressionNode* _node;
    llvm::BinaryOperator* _irValue;
    IRExpressionNode* _irLeftNode;
    IRExpressionNode* _irRightNode;
    IRType* _type;
public:
    IRBinaryArithmeticExpressionNode(ASTBinaryExpressionNode* astNode, llvm::BinaryOperator* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, IRType* type);
    std::vector<IRExpressionNode*> getListOfOperands();
    std::vector<IRBinaryOperatorNode*> getListOfOperations();
    void markAsGlobal() override;
    bool isReferenced() override;
    llvm::BinaryOperator* getValue() override;
    IRExpressionNode* getLeftNode();
    IRExpressionNode* getRightNode();
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_BINARY_ARITHMETIC_EXPRESSION_NODE_H
