//
// Created by Johny Georges on 2025-03-19.
//

#ifndef JETLANG_IR_DREF_EXPRESSION_NODE_H
#define JETLANG_IR_DREF_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../ir-literal-nodes/ir-literal-node.h"
#include "../../ir-type/ir-pointer-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-ref-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-dref-expression-node.h"

class IRDrefExpressionNode : public IRExpressionNode {
private:
    ASTDrefExpressionNode* _node;
    IRExpressionNode* _irExpression;
    IRType* _irType;
    IRInstructionNode* _irValue;
public:
    IRDrefExpressionNode(ASTDrefExpressionNode* node, IRExpressionNode* irExpression, IRType* irType, IRInstructionNode* irValue);
    void markAsGlobal() override;
    IRExpressionNode* getExpression();
    IRInstructionNode* getIRValue();
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_DREF_EXPRESSION_NODE_H
