//
// Created by Johny Georges on 2024-07-02.
//

#ifndef JETLANG_IR_LITERAL_EXPRESSION_NODE_H
#define JETLANG_IR_LITERAL_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../ir-literal-nodes/ir-literal-node.h"
#include "ir-constant-expression-node.h"

class IRLiteralExpressionNode : public IRConstantExpressionNode {
private:
    ASTLiteralExpressionNode* _astNode;
    IRLiteralNode* _irValue;
public:
    IRLiteralExpressionNode(ASTLiteralExpressionNode* astNode, IRLiteralNode* irValue);
    llvm::Value * insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value *parent) override;
    llvm::Constant* getIRValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};


#endif //JETLANG_IR_LITERAL_EXPRESSION_NODE_H
