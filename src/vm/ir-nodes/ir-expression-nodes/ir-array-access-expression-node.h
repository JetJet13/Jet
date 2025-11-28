//
// Created by Johny Georges on 2024-07-06.
//

#ifndef JETLANG_IR_ARRAY_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_ARRAY_ACCESS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-access-expression-node.h"
#include "ir-expression-node.h"

class IRArrayAccessExpressionNode : public IRExpressionNode {
protected:
    ASTArrayAccessExpressionNode* _node;
    IRExpressionNode* _irSource;
    IRExpressionNode* _irIndex;
    IRType* _type;
    std::optional<IRInstructionNode*> _sourceAllocation;
public:
    IRArrayAccessExpressionNode(ASTArrayAccessExpressionNode* node, IRExpressionNode* irSource, IRExpressionNode* irIndex, IRType* type, std::optional<IRInstructionNode*> sourceAllocation);
    void markAsGlobal() override;
    bool isReferenced() override;
    IRExpressionNode* getSourceExpression();
    IRExpressionNode* getIndexExpression();
    ASTArrayAccessExpressionNode* getNode();
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    llvm::Value* getValue() override;
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_ARRAY_ACCESS_EXPRESSION_NODE_H
