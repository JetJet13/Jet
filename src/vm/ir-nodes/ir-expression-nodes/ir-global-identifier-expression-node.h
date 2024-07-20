//
// Created by Johny Georges on 2024-07-17.
//

#ifndef JETLANG_IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE_H
#define JETLANG_IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "ir-expression-node.h"

class IRGlobalIdentifierExpressionNode : public IRExpressionNode {
private:
    ASTIdentifierExpressionNode* _node;
    llvm::GlobalVariable* _irValue;
public:
    IRGlobalIdentifierExpressionNode(ASTIdentifierExpressionNode* node, llvm::GlobalVariable* irValue);
    llvm::GlobalVariable* insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::GlobalVariable* getIRValue() override;
    llvm::Type* getType() override;
    llvm::Type* getTypeAtIndex(unsigned long index) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE_H
