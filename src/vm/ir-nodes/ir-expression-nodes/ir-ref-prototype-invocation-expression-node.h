//
// Created by Johny Georges on 2025-10-25.
//

#ifndef JETLANG_IR_REF_PROTOTYPE_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_REF_PROTOTYPE_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-invocation-expression-node.h"
#include "../ir-function-nodes/ir-function-argument-node.h"

class IRRefPrototypeInvocationExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTObjectAccessInvocationExpressionNode> _node;
    llvm::CallInst* _irCallInstruction;
    llvm::Value* _irFunction;
    IRType* _irFunctionType;
    std::vector<IRFunctionArgumentNode*> _arguments;
    IRType* _type;
    IRExpressionNode* _irRef;
public:
    IRRefPrototypeInvocationExpressionNode(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> node, llvm::Value* irFunction, llvm::CallInst* irCallInstruction, IRType* irFunctionType, std::vector<IRFunctionArgumentNode*> arguments, IRType* type, IRExpressionNode* irRef);
    void markAsGlobal() override;
    IRExpressionNode* getIRRefValue();
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

#endif //JETLANG_IR_REF_PROTOTYPE_INVOCATION_EXPRESSION_NODE_H
