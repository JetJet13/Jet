//
// Created by Johny Georges on 2024-11-14.
//

#ifndef JETLANG_IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H
#define JETLANG_IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H

#include <llvm/IR/Function.h>
#include "../../ir-block-nodes/ir-block-node.h"
#include "../../ir-function-nodes/ir-function-parameter-list-node.h"
#include "../../../ir-type/ir-lambda-type.h"
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-lambda-with-fat-arrow-expression-node.h"
#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "ir-lambda-expression-node.h"

class IRLambdaWithFatArrowExpressionNode : public IRLambdaExpressionNode {
private:
    std::shared_ptr<ASTLambdaWithFatArrowExpressionNode> _node;
    llvm::Function* _irFunction;
    IRInstructionNode* _irValue;
    IRFunctionParameterListNode* _irParameterList;
    IRBlockNode* _irBlock;
    IRLambdaType* _type;
    llvm::Function* _irCleanupFunction;
    IRExpressionNode* _irReturnExpression;
public:
    IRLambdaWithFatArrowExpressionNode(std::shared_ptr<ASTLambdaWithFatArrowExpressionNode> node, IRInstructionNode* irValue, llvm::Function* irFunction, IRFunctionParameterListNode* irParameterList, IRBlockNode* irBlock, IRLambdaType* type, llvm::Function* irCleanupFunction, IRExpressionNode* irReturnExpression);
    IRExpressionNode* getReturnExpression();
    IRInstructionNode* getAllocation() override;
    llvm::Function* getFunctionValue() override;
    llvm::Function* getCleanupFunction() override;
    IRBlockNode* getBlock() override;
    IRFunctionParameterListNode* getParameters() override;
    llvm::Value* getValue() override;
    IRLambdaType* getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H
