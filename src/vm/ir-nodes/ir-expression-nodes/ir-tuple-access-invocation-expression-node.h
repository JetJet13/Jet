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
    IRExpressionNode* _source;
    int64_t _targetIndex;
    IRType* _irFunctionType;
    std::vector<IRFunctionArgumentNode*> _arguments;
    IRType* _type;
public:
    IRTupleAccessInvocationExpressionNode(std::shared_ptr<ASTTupleAccessInvocationExpressionNode> node, IRExpressionNode* source, llvm::CallInst* irCallInstruction, IRType* irFunctionType, int64_t targetIndex, std::vector<IRFunctionArgumentNode*> arguments, IRType* type);
    void markAsGlobal() override;
    IRExpressionNode* getSource();
    std::vector<IRFunctionArgumentNode*>* getIRArguments();
    llvm::CallInst* getValue() override;
    IRType* getFunctionIRType();
    int64_t getTargetIndex();
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE_H
