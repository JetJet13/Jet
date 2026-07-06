//
// Created by Johny Georges on 2025-06-19.
//

#ifndef JETLANG_IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-access-invocation-expression-node.h"
#include "ir-tuple-access-expression-node.h"
#include "../ir-function-nodes/ir-function-argument-node.h"

class IRTupleAccessInvocationExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTTupleAccessInvocationExpressionNode> _node;
    llvm::CallInst* _irCallInstruction;
    std::shared_ptr<IRExpressionNode> _source;
    int64_t _targetIndex;
    std::shared_ptr<IRType> _irFunctionType;
    std::vector<std::shared_ptr<IRFunctionArgumentNode>> _arguments;
    std::shared_ptr<IRType> _type;
public:
    IRTupleAccessInvocationExpressionNode(std::shared_ptr<ASTTupleAccessInvocationExpressionNode> node, std::shared_ptr<IRExpressionNode> source, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, int64_t targetIndex, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRType> type);
    void markAsGlobal() override;
    std::shared_ptr<IRExpressionNode> getSource();
    std::vector<std::shared_ptr<IRFunctionArgumentNode>>* getIRArguments();
    llvm::CallInst* getValue() override;
    std::shared_ptr<IRType> getFunctionIRType();
    int64_t getTargetIndex();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE_H
