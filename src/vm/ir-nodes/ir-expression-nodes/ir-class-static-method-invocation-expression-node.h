//
// Created by Johny Georges on 2026-03-16.
//

#ifndef JETLANG_IR_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-access-invocation-expression-node.h"
#include "ir-tuple-access-expression-node.h"
#include "ir-object-access-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-invocation-expression-node.h"
#include "../ir-function-nodes/ir-function-argument-node.h"

class IRClassStaticMethodInvocationExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTObjectAccessInvocationExpressionNode> _node;
    llvm::CallInst* _irCallInstruction;
    IRInstructionNode* _irFunction;
    IRType* _irFunctionType;
    std::vector<IRFunctionArgumentNode*> _arguments;
    IRType* _type;
public:
    IRClassStaticMethodInvocationExpressionNode(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> node, IRInstructionNode* irFunction, llvm::CallInst* irCallInstruction, IRType* irFunctionType, std::vector<IRFunctionArgumentNode*> arguments, IRType* type);
    void markAsGlobal() override;
    IRInstructionNode* getFunction();
    std::vector<IRFunctionArgumentNode*>* getIRArguments();
    llvm::CallInst* getValue() override;
    llvm::Value* getFunctionValue();
    IRType* getFunctionIRType();
    IRType* getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_NODE_H
