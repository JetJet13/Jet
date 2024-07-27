//
// Created by Johny Georges on 2024-07-16.
//

#ifndef JETLANG_IR_OBJECT_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_OBJECT_ACCESS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-expression-node.h"
#include "../../ir-type/ir-struct-type.h"

class IRObjectAccessExpressionNode : public IRExpressionNode {
private:
    ASTObjectAccessExpressionNode* _node;
    IRExpressionNode* _irSource;
    std::string _targetKey;
    unsigned long _targetKeyIndex;
    llvm::Constant* _irTargetKeyIndex;
public:
    IRObjectAccessExpressionNode(ASTObjectAccessExpressionNode* node, IRExpressionNode* irSource, std::string targetKey, unsigned long targetKeyIndex, llvm::Constant* irTargetKeyIndex);
    llvm::Value* insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    IRType* getIRType() override;
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_OBJECT_ACCESS_EXPRESSION_NODE_H
