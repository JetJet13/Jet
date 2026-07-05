//
// Created by Johny Georges on 2024-07-16.
//

#ifndef JETLANG_IR_OBJECT_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_OBJECT_ACCESS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-expression-node.h"
#include "../../ir-type/ir-struct-type.h"

class IRObjectAccessExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTObjectAccessExpressionNode> _node;
    IRExpressionNode* _irSource;
    std::string _targetKey;
    unsigned long _targetKeyIndex;
    llvm::Constant* _irTargetKeyIndex;
    std::shared_ptr<IRType> _irType;
    std::optional<IRInstructionNode*> _sourceAllocation;
public:
    IRObjectAccessExpressionNode(std::shared_ptr<ASTObjectAccessExpressionNode> node, IRExpressionNode* irSource, std::string targetKey, unsigned long targetKeyIndex, llvm::Constant* irTargetKeyIndex, std::shared_ptr<IRType> irType, std::optional<IRInstructionNode*> sourceAllocation = {});
    void markAsGlobal() override;
    std::shared_ptr<ASTObjectAccessExpressionNode> getNode();
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    std::optional<IRInstructionNode*> getArc() override;
    IRExpressionNode* getSource();
    std::string* getTargetKey();
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

#endif //JETLANG_IR_OBJECT_ACCESS_EXPRESSION_NODE_H
