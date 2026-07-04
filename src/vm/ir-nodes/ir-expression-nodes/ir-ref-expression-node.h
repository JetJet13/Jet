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
#include "../../ir-type/ir-ref-type.h"

class IRRefExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTRefExpressionNode> _node;
    IRExpressionNode* _irExpression;
    IRRefType* _irType;
    IRInstructionNode* _irValue;
    IRInstructionNode* _irArc;
public:
    IRRefExpressionNode(std::shared_ptr<ASTRefExpressionNode> node, IRExpressionNode* irExpression, IRRefType* irType, IRInstructionNode* irValue, IRInstructionNode* irArc);
    void markAsGlobal() override;
    IRExpressionNode* getExpression();
    IRInstructionNode* getIRValue();
    IRRefType* getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    std::optional<IRInstructionNode*> getArc() override;
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_REF_EXPRESSION_NODE_H
