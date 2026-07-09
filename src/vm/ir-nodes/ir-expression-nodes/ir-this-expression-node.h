//
// Created by Johny Georges on 2026-06-15.
//

#ifndef JETLANG_IR_THIS_EXPRESSION_NODE_H
#define JETLANG_IR_THIS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-this-expression-node.h"

class IRThisExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTThisExpressionNode> _node;
    std::shared_ptr<IRInstructionNode> _irValue;
    std::shared_ptr<IRPointerType> _irType;
public:
    IRThisExpressionNode(std::shared_ptr<ASTThisExpressionNode> node, std::shared_ptr<IRInstructionNode> irValue);
    std::shared_ptr<IRInstructionNode> getIRValue();
    std::optional<std::shared_ptr<IRInstructionNode>> getSourceAllocation() override;
    llvm::Value* getValue() override;
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream>* stream) override;
};

#endif //JETLANG_IR_THIS_EXPRESSION_NODE_H
