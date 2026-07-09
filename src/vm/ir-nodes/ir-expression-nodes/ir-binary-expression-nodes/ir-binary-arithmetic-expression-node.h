//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_BINARY_ARITHMETIC_EXPRESSION_NODE_H
#define JETLANG_IR_BINARY_ARITHMETIC_EXPRESSION_NODE_H

#include <llvm/IR/InstrTypes.h>
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-binary-arithmetic-expression-node.h"
#include "ir-binary-expression-node.h"
#include "../../ir-binary-operator-node.h"

class IRBinaryArithmeticExpressionNode : public IRBinaryExpressionNode {
private:
    std::shared_ptr<ASTBinaryArithmeticExpressionNode> _node;
    llvm::BinaryOperator* _irValue;
    std::shared_ptr<IRExpressionNode> _irLeftNode;
    std::shared_ptr<IRExpressionNode> _irRightNode;
    std::shared_ptr<IRType> _type;
public:
    IRBinaryArithmeticExpressionNode(std::shared_ptr<ASTBinaryArithmeticExpressionNode> astNode, llvm::BinaryOperator* irValue, std::shared_ptr<IRExpressionNode> irLeftNode, std::shared_ptr<IRExpressionNode> irRightNode, std::shared_ptr<IRType> type);
    std::vector<std::shared_ptr<IRExpressionNode>> getListOfOperands();
    std::vector<std::shared_ptr<IRBinaryOperatorNode>> getListOfOperations();
    void markAsGlobal() override;
    llvm::BinaryOperator* getValue() override;
    std::shared_ptr<IRExpressionNode> getLeftNode();
    std::shared_ptr<IRExpressionNode> getRightNode();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_BINARY_ARITHMETIC_EXPRESSION_NODE_H
