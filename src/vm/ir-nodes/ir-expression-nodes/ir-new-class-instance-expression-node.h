//
// Created by Johny Georges on 2024-12-30.
//

#ifndef JETLANG_IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE_H
#define JETLANG_IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"
#include "../../../core/type-signature/class-type-signature/new-class-instance-type-signature/new-class-instance-type-signature.h"
#include "../../ir-type/ir-class-type.h"
#include "../../ir-type/ir-new-class-instance-type.h"
#include "../ir-function-nodes/ir-function-argument-node.h"

class IRNewClassInstanceExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTNewClassInstanceExpressionNode> _node;
    std::string _constructorId;
    IRFunctionType* _irConstructorType;
    std::vector<IRFunctionArgumentNode*> _arguments;
    IRNewClassInstanceType* _type;
    IRInstructionNode* _classInstanceAllocation;
    IRInstructionNode* _irArc;
public:
    IRNewClassInstanceExpressionNode(std::shared_ptr<ASTNewClassInstanceExpressionNode> node, std::string constructorId, IRFunctionType* irConstructorType, std::vector<IRFunctionArgumentNode*> arguments, IRNewClassInstanceType* type, IRInstructionNode* classInstanceAllocation, IRInstructionNode* irArc);
    void markAsGlobal() override;
    IRInstructionNode* getClassInstanceAllocation();
    std::vector<IRFunctionArgumentNode*>* getIRArguments();
    std::optional<IRInstructionNode*> getArc() override;
    llvm::Value* getValue() override;
    IRFunctionType* getConstructorIRType();
    std::string getConstructorId();
    IRNewClassInstanceType* getIRType() override;
    NewClassInstanceTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE_H
