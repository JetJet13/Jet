//
// Created by Johny Georges on 2024-11-14.
//

#ifndef JETLANG_IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H
#define JETLANG_IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H

#include <llvm/IR/Function.h>
#include "../ir-block-nodes/ir-block-node.h"
#include "../ir-function-nodes/ir-function-parameter-list-node.h"
#include "ir-expression-node.h"
#include "../../ir-type/ir-lambda-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-lambda-with-fat-arrow-expression-node.h"

class IRLambdaWithFatArrowExpressionNode : public IRExpressionNode {
private:
    ASTLambdaWithFatArrowExpressionNode* _node;
    llvm::Function* _irValue;
    IRFunctionParameterListNode* _irParameterList;
    IRBlockNode* _irBlock;
    IRLambdaType* _type;
    llvm::Function* _irCleanupFunction;
public:
    IRLambdaWithFatArrowExpressionNode(ASTLambdaWithFatArrowExpressionNode* node, llvm::Function* irValue, IRFunctionParameterListNode* irParameterList, IRBlockNode* irBlock, IRLambdaType* type, llvm::Function* irCleanupFunction);
    llvm::Function* getCleanupFunction();
    llvm::Function* getValue() override;
    IRLambdaType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H
