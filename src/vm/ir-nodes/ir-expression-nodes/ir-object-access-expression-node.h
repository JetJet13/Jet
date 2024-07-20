//
// Created by Johny Georges on 2024-07-16.
//

#ifndef JETLANG_IR_OBJECT_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_OBJECT_ACCESS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-expression-node.h"


class IRObjectAccessExpressionNode : public IRExpressionNode {
private:
    ASTObjectAccessExpressionNode* _node;
    IRExpressionNode* _irSource;
    unsigned long _targetKeyIndex;
    llvm::Constant* _irTargetKeyIndex;
public:
    IRObjectAccessExpressionNode(ASTObjectAccessExpressionNode* node, IRExpressionNode* irSource, unsigned long targetKeyIndex, llvm::Constant* irTargetKeyIndex);
    llvm::Value* insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_OBJECT_ACCESS_EXPRESSION_NODE_H
