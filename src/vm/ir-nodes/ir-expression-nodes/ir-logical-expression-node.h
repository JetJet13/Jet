//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_LOGICAL_EXPRESSION_NODE_H
#define JETLANG_IR_LOGICAL_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/InstrTypes.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"
#include "ir-expression-node.h"

class IRLogicalExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTLogicalExpressionNode> _node;
    llvm::BinaryOperator* _irValue;
    std::shared_ptr<IRExpressionNode> _irLeftNode;
    std::shared_ptr<IRExpressionNode> _irRightNode;
    std::shared_ptr<IRType> _type;
public:
    IRLogicalExpressionNode(std::shared_ptr<ASTLogicalExpressionNode> astNode, llvm::BinaryOperator* irValue, std::shared_ptr<IRType> type, std::shared_ptr<IRExpressionNode> irLeftNode, std::shared_ptr<IRExpressionNode> irRightNode);
    void markAsGlobal() override;
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    llvm::BinaryOperator* getValue() override;
    std::shared_ptr<IRExpressionNode> getLeftNode();
    std::shared_ptr<IRExpressionNode> getRightNode();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_LOGICAL_EXPRESSION_NODE_H
