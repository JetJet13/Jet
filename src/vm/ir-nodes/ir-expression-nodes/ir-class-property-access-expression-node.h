//
// Created by Johny Georges on 2024-12-14.
//

#ifndef JETLANG_IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "ir-expression-node.h"
#include "../../ir-type/ir-struct-ref-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-class-property-access-expression-node.h"

class IRClassPropertyAccessExpressionNode : public IRExpressionNode {
private:
    ASTClassPropertyAccessExpressionNode* _node;
    IRInstructionNode* _irSource;
    std::string _targetKey;
    unsigned long _targetKeyIndex;
    llvm::Constant* _irTargetKeyIndex;
    IRType* _irType;
    std::optional<IRInstructionNode*> _sourceAllocation;
public:
    IRClassPropertyAccessExpressionNode(ASTClassPropertyAccessExpressionNode* node, IRInstructionNode* irSource, std::string targetKey, unsigned long targetKeyIndex, llvm::Constant* irTargetKeyIndex, IRType* irType, std::optional<IRInstructionNode*> sourceAllocation = {});
    ASTClassPropertyAccessExpressionNode* getNode();
    IRInstructionNode* getSource();
    std::string* getTargetKey();
    llvm::Constant* getIRTargetKeyIndex();
    unsigned long getTargetKeyIndex();
    std::optional<IRInstructionNode*> getSourceAllocation() override;
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

#endif //JETLANG_IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE_H
