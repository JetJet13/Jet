//
// Created by Johny Georges on 2025-02-10.
//

#ifndef JETLANG_IR_REF_EXPRESSION_NODE_H
#define JETLANG_IR_REF_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../ir-literal-nodes/ir-literal-node.h"
#include "../../ir-type/ir-pointer-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-ref-expression-node.h"

class IRRefExpressionNode : public IRExpressionNode {
private:
    ASTRefExpressionNode* _node;
    IRExpressionNode* _irExpression;
    IRPointerType* _irType;
public:
    IRRefExpressionNode(ASTRefExpressionNode* node, IRExpressionNode* irValue, IRPointerType* irType);
    void markAsGlobal() override;
    IRExpressionNode* getExpression();
    IRPointerType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_REF_EXPRESSION_NODE_H
