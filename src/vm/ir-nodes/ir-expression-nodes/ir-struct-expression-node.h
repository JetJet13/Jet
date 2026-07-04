//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_STRUCT_EXPRESSION_NODE_H
#define JETLANG_IR_STRUCT_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Instructions.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-struct-ref-type.h"

class IRStructExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTStructExpressionNode> _node;
    IRInstructionNode* _irValue;
    IRInstructionNode* _irArc;
    std::vector<IRExpressionNode*> _irValues;
    IRStructRefType* _type;
public:
    IRStructExpressionNode(std::shared_ptr<ASTStructExpressionNode> astNode, IRInstructionNode* irValue, IRInstructionNode* irArc, IRStructRefType* type, std::vector<IRExpressionNode*> irValues);
    void markAsGlobal() override;
    IRStructRefType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    std::optional<IRInstructionNode*> getArc() override;
    unsigned long size();
    llvm::Value* getValue() override;
    IRInstructionNode* getIRValue();
    std::vector<IRExpressionNode*>* getValues();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_STRUCT_EXPRESSION_NODE_H
