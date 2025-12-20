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
#include "../../ir-type/ir-struct-pointer-type.h"

class IRTupleExpressionNode : public IRExpressionNode {
private:
    ASTTupleExpressionNode* _node;
    IRInstructionNode* _irValue;
    std::vector<IRExpressionNode*> _irValues;
    IRStructRefType* _type;
public:
    IRTupleExpressionNode(ASTTupleExpressionNode* node, IRInstructionNode* irValue, IRStructRefType* type, std::vector<IRExpressionNode*> irValues);
    void markAsGlobal() override;
    bool isReferenced() override;
    llvm::Value* getValue() override;
    unsigned long size();
    IRInstructionNode* getIRValue();
    std::vector<IRExpressionNode*>* getValues();
    IRStructRefType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_TUPLE_EXPRESSION_NODE_H
