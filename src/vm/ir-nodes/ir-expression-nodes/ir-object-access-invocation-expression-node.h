//
// Created by Johny Georges on 2025-06-20.
//

#ifndef JETLANG_IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-access-invocation-expression-node.h"
#include "ir-tuple-access-expression-node.h"
#include "ir-object-access-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-invocation-expression-node.h"
#include "../ir-function-nodes/ir-function-argument-node.h"

class IRObjectAccessInvocationExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTObjectAccessInvocationExpressionNode> _node;
    llvm::CallInst* _irCallInstruction;
    std::shared_ptr<IRExpressionNode> _source;
    int64_t _targetIndex;
    std::shared_ptr<IRType> _irFunctionType;
    std::vector<std::shared_ptr<IRFunctionArgumentNode>> _arguments;
    std::shared_ptr<IRType> _type;
    std::optional<std::shared_ptr<IRExpressionNode>> _scopeArgument;
public:
    IRObjectAccessInvocationExpressionNode(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> node, std::shared_ptr<IRExpressionNode> source, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, int64_t targetIndex, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRType> type, std::optional<std::shared_ptr<IRExpressionNode>> scopeArgument = {});
    void markAsGlobal() override;
    std::shared_ptr<IRExpressionNode> getSource();
    std::optional<std::shared_ptr<IRExpressionNode>> getScopeArgument();
    std::vector<std::shared_ptr<IRFunctionArgumentNode>>* getIRArguments();
    llvm::CallInst* getValue() override;
    int64_t getTargetIndex();
    std::shared_ptr<IRType> getFunctionIRType();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE_H
