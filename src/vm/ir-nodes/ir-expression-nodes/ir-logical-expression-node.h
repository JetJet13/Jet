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
    ASTLogicalExpressionNode* _node;
    llvm::BinaryOperator* _irValue;
    IRExpressionNode* _irLeftNode;
    IRExpressionNode* _irRightNode;
    IRType* _type;
public:
    IRLogicalExpressionNode(ASTLogicalExpressionNode* astNode, llvm::BinaryOperator* irValue, IRType* type, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode);
    void markAsGlobal() override;
    bool isReferenced() override;
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    llvm::BinaryOperator* getValue() override;
    IRExpressionNode* getLeftNode();
    IRExpressionNode* getRightNode();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_LOGICAL_EXPRESSION_NODE_H
