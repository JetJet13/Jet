//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_IDENTIFIER_EXPRESSION_NODE_H
#define JETLANG_IR_IDENTIFIER_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "ir-expression-node.h"
#include "../ir-allocation-node.h"

class IRIdentifierExpressionNode : public IRExpressionNode {
private:
    ASTIdentifierExpressionNode* _node;
    IRAllocationNode* _irValue;
public:
    IRIdentifierExpressionNode(ASTIdentifierExpressionNode* node, IRAllocationNode* irValue);
    llvm::Value* insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::Value* getValue() override;
    IRType* getIRType() override;
    llvm::Type* getTypeAtIndex(unsigned long index) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_IDENTIFIER_EXPRESSION_NODE_H
