//
// Created by Johny Georges on 2024-11-12.
//

#ifndef JETLANG_IR_LAMBDA_EXPRESSION_NODE_H
#define JETLANG_IR_LAMBDA_EXPRESSION_NODE_H

#include <llvm/IR/Function.h>
#include "../ir-block-nodes/ir-block-node.h"
#include "../ir-function-nodes/ir-function-parameter-list-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"
#include "ir-expression-node.h"
#include "../../ir-type/ir-lambda-type.h"

class IRLambdaExpressionNode : public IRExpressionNode {
private:
    ASTLambdaExpressionNode* _node;
    llvm::Function* _irValue;
    IRFunctionParameterListNode* _irParameterList;
    IRBlockNode* _irBlock;
    IRLambdaType* _type;
public:
    IRLambdaExpressionNode(ASTLambdaExpressionNode* node, llvm::Function* irValue, IRFunctionParameterListNode* irParameterList, IRBlockNode* irBlock, IRLambdaType* type);
    llvm::Function* getValue() override;
    IRLambdaType* getIRType() override;
    LambdaExpressionTypeSignature* getTypeSignature() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_LAMBDA_EXPRESSION_NODE_H
