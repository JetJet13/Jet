//
// Created by Johny Georges on 2024-10-09.
//

#ifndef JETLANG_IR_TUPLE_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_TUPLE_ACCESS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-access-expression.h"
#include "../../ir-type/ir-struct-ref-type.h"

class IRTupleAccessExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTTupleAccessExpressionNode> _node;
    std::shared_ptr<IRExpressionNode> _irSource;
    unsigned long _targetKeyIndex;
    llvm::Constant* _irTargetKeyIndex;
    std::shared_ptr<IRType> _irType;
    std::optional<std::shared_ptr<IRInstructionNode>> _sourceAllocation;
public:
    IRTupleAccessExpressionNode(std::shared_ptr<ASTTupleAccessExpressionNode> node, std::shared_ptr<IRExpressionNode> irSource, unsigned long targetKeyIndex, llvm::Constant* irTargetKeyIndex, std::shared_ptr<IRType> irType, std::optional<std::shared_ptr<IRInstructionNode>> sourceAllocation = {});
    void markAsGlobal() override;
    std::optional<std::shared_ptr<IRInstructionNode>> getSourceAllocation() override;
    std::optional<std::shared_ptr<IRInstructionNode>> getArc() override;
    std::shared_ptr<IRExpressionNode> getSource();
    llvm::Constant* getIRTargetKeyIndex();
    unsigned long getTargetKeyIndex();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    std::shared_ptr<IRType> getTargetIRType();
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};


#endif //JETLANG_IR_TUPLE_ACCESS_EXPRESSION_NODE_H
