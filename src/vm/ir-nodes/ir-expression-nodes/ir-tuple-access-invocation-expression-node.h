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

class IRTupleAccessInvocationExpressionNode : public IRExpressionNode {
private:
    ASTTupleAccessInvocationExpressionNode* _node;
    IRTupleAccessExpressionNode* _irTupleAccessExpression;
    IRType* _irFunctionType;
    std::vector<IRExpressionNode*> _arguments;
    IRType* _type;
public:
    IRTupleAccessInvocationExpressionNode(ASTTupleAccessInvocationExpressionNode* node, IRTupleAccessExpressionNode* irTupleAccessExpression, IRType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type);
    void markAsGlobal() override;
    bool isReferenced() override;
    IRTupleAccessExpressionNode* getIRTupleAccessExpression();
    std::vector<IRExpressionNode*>* getIRArguments();
    llvm::Value* getValue() override;
    IRType* getFunctionIRType();
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE_H
