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
    ASTTupleAccessExpressionNode* _node;
    IRExpressionNode* _irSource;
    unsigned long _targetKeyIndex;
    llvm::Constant* _irTargetKeyIndex;
    IRType* _irType;
    std::optional<IRInstructionNode*> _sourceAllocation;
public:
    IRTupleAccessExpressionNode(ASTTupleAccessExpressionNode* node, IRExpressionNode* irSource, unsigned long targetKeyIndex, llvm::Constant* irTargetKeyIndex, IRType* irType, std::optional<IRInstructionNode*> sourceAllocation = {});
    void markAsGlobal() override;
    bool isReferenced() override;
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    std::optional<IRInstructionNode*> getArc() override;
    IRExpressionNode* getSource();
    llvm::Constant* getIRTargetKeyIndex();
    unsigned long getTargetKeyIndex();
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRType* getTargetIRType();
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};


#endif //JETLANG_IR_TUPLE_ACCESS_EXPRESSION_NODE_H
