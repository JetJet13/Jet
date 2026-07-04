//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_TUPLE_EXPRESSION_NODE_H
#define JETLANG_IR_TUPLE_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include "../ir-node.h"
#include "../ir-instruction-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-expression-node.h"
#include "ir-expression-node.h"
#include "../../ir-type/ir-struct-ref-type.h"

class IRTupleExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTTupleExpressionNode> _node;
    IRInstructionNode* _irValue;
    IRInstructionNode* _irArc;
    std::vector<IRExpressionNode*> _irValues;
    IRStructRefType* _type;
public:
    IRTupleExpressionNode(std::shared_ptr<ASTTupleExpressionNode> node, IRInstructionNode* irValue, IRInstructionNode* irArc, IRStructRefType* type, std::vector<IRExpressionNode*> irValues);
    void markAsGlobal() override;
    llvm::Value* getValue() override;
    unsigned long size();
    IRInstructionNode* getIRValue();
    std::vector<IRExpressionNode*>* getValues();
    std::optional<IRInstructionNode*> getArc() override;
    IRStructRefType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_TUPLE_EXPRESSION_NODE_H
