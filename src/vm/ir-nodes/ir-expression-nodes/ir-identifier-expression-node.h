//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_IDENTIFIER_EXPRESSION_NODE_H
#define JETLANG_IR_IDENTIFIER_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "ir-expression-node.h"

class IRIdentifierExpressionNode : public IRExpressionNode {
private:
    ASTIdentifierExpressionNode* _astNode;
    IRNode* _irNode;
public:
    IRIdentifierExpressionNode(ASTIdentifierExpressionNode* astNode, IRNode* irNode);
    llvm::Value * insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value *variableAllocation) override;
    llvm::Value* getIRValue() override;
    llvm::Type* getIRTypeAtIndex(unsigned long index) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_IDENTIFIER_EXPRESSION_NODE_H
