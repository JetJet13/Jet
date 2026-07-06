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
    std::shared_ptr<IRExpressionNode> _irExpression;
    std::shared_ptr<IRRefType> _irType;
    std::shared_ptr<IRInstructionNode> _irValue;
    std::shared_ptr<IRInstructionNode> _irArc;
public:
    IRRefExpressionNode(std::shared_ptr<ASTRefExpressionNode> node, std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRRefType> irType, std::shared_ptr<IRInstructionNode> irValue, std::shared_ptr<IRInstructionNode> irArc);
    void markAsGlobal() override;
    std::shared_ptr<IRExpressionNode> getExpression();
    std::shared_ptr<IRInstructionNode> getIRValue();
    std::shared_ptr<IRRefType> getIRRefType();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    std::optional<std::shared_ptr<IRInstructionNode>> getSourceAllocation() override;
    std::optional<std::shared_ptr<IRInstructionNode>> getArc() override;
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_REF_EXPRESSION_NODE_H
