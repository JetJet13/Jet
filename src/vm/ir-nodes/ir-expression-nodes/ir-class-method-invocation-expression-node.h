//
// Created by Johny Georges on 2024-12-27.
//

#ifndef JETLANG_IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-class-method-invocation-expression-node.h"

class IRClassMethodInvocationExpressionNode : public IRExpressionNode {
private:
    ASTClassMethodInvocationExpressionNode* _node;
    llvm::Value* _irFunction;
    IRType* _irFunctionType;
    std::vector<IRExpressionNode*> _arguments;
    IRType* _type;
    IRInstructionNode* _classScopeArgument;
public:
    IRClassMethodInvocationExpressionNode(ASTClassMethodInvocationExpressionNode* node, llvm::Value* irFunction, IRType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type, IRInstructionNode* classScopeArgument);
    void markAsGlobal() override;
    IRInstructionNode* getClassScopeArgument();
    std::vector<IRExpressionNode*>* getIRArguments();
    llvm::Value* getValue() override;
    IRType* getFunctionIRType();
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE_H
