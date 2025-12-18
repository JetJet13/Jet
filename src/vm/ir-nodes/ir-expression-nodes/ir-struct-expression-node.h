//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_STRUCT_EXPRESSION_NODE_H
#define JETLANG_IR_STRUCT_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Instructions.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"
#include "ir-expression-node.h"
#include "../../ir-type/ir-struct-type.h"
#include "../ir-instruction-node.h"

class IRStructExpressionNode : public IRExpressionNode {
private:
    ASTStructExpressionNode* _node;
    IRInstructionNode* _irValue;
    std::vector<IRExpressionNode*> _irValues;
    IRStructType* _type;
public:
    IRStructExpressionNode(ASTStructExpressionNode* astNode, IRInstructionNode* irValue, IRStructType* type, std::vector<IRExpressionNode*> irValues);
    void markAsGlobal() override;
    bool isReferenced() override;
    IRStructType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    unsigned long size();
    llvm::Value* getValue() override;
    IRInstructionNode* getIRValue();
    std::vector<IRExpressionNode*>* getValues();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_STRUCT_EXPRESSION_NODE_H
