//
// Created by Johny Georges on 2026-07-13.
//

#ifndef JETLANG_IR_SHARE_EXPRESSION_NODE_H
#define JETLANG_IR_SHARE_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../ir-literal-nodes/ir-literal-node.h"
#include "../../ir-type/ir-pointer-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-share-expression-node.h"
#include "../../ir-type/ir-shared-ptr-type.h"

class IRShareExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTShareExpressionNode> _node;
    std::shared_ptr<IRExpressionNode> _irExpression;
    std::shared_ptr<IRSharedPtrType> _irType;
    std::shared_ptr<IRInstructionNode> _irValue;
    std::shared_ptr<IRInstructionNode> _irArc;
public:
    IRShareExpressionNode(std::shared_ptr<ASTShareExpressionNode> node, std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRSharedPtrType> irType, std::shared_ptr<IRInstructionNode> irValue, std::shared_ptr<IRInstructionNode> irArc);
    void markAsGlobal() override;
    std::shared_ptr<IRExpressionNode> getExpression();
    std::shared_ptr<IRInstructionNode> getIRValue();
    std::shared_ptr<IRSharedPtrType> getIRSharedPtrType();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    std::optional<std::shared_ptr<IRInstructionNode>> getSourceAllocation() override;
    std::optional<std::shared_ptr<IRInstructionNode>> getArc() override;
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_SHARE_EXPRESSION_NODE_H
