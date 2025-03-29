//
// Created by Johny Georges on 2025-03-29.
//

#ifndef JETLANG_IR_SREF_EXPRESSION_NODE_H
#define JETLANG_IR_SREF_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../ir-literal-nodes/ir-literal-node.h"
#include "../../ir-type/ir-pointer-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-sref-expression-node.h"

class IRSrefExpressionNode : public IRExpressionNode {
private:
    ASTSrefExpressionNode* _node;
    IRExpressionNode* _irExpression;
    IRPointerType* _irType;
    IRInstructionNode* _irValue;
public:
    IRSrefExpressionNode(ASTSrefExpressionNode* node, IRExpressionNode* irExpression, IRPointerType* irType, IRInstructionNode* irValue);
    void markAsGlobal() override;
    IRExpressionNode* getExpression();
    IRInstructionNode* getIRValue();
    IRPointerType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_SREF_EXPRESSION_NODE_H
