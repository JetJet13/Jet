//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_VARIABLE_DECLARATION_NODE_H
#define JETLANG_IR_VARIABLE_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-declaration-node.h"

class IRVariableDeclarationNode : public IRDeclarationNode {
private:
    ASTVariableDeclarationNode* _astNode;
    llvm::AllocaInst* _irValue;
    IRExpressionNode* _irExpression;
public:
    IRVariableDeclarationNode(ASTVariableDeclarationNode* astNode, llvm::AllocaInst* irValue, IRExpressionNode* irExpression);
    void insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_VARIABLE_DECLARATION_NODE_H
