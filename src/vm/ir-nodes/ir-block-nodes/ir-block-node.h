//
// Created by Johny Georges on 2024-07-05.
//

#ifndef JETLANG_IR_BLOCK_NODE_H
#define JETLANG_IR_BLOCK_NODE_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/BasicBlock.h"
#include "../ir-node.h"
#include "../ir-declaration-nodes/ir-variable-declaration-node.h"
#include "../ir-statement-nodes/ir-function-return-expression-node.h"
#include "../../types/ir-block-type.h"
#include "../ir-function-nodes/ir-function-parameter-node.h"
#include "../../ir-lookup-table/ir-lookup-table.h"
#include "../ir-node-to-free.h"

class IRBlockNode {
protected:
    llvm::BasicBlock* _irValue;
    IRBlockType _type;
    IRLookupTable* _scope;
    std::unique_ptr<llvm::IRBuilder<>> _builder;
    std::vector<IRNode*> _body;
    std::vector<IRBlockNode*> _successors;
    std::optional<IRBlockNode*> _parentBlock;
    std::vector<IRNodeToFree*> _nodesToFree;
    std::vector<IRExpressionNode*> _expressionsToFree;
    std::vector<IRVariableDeclarationNode*> _variablesToFree;
    std::vector<IRVariableDeclarationNode*> _lambdaVariablesToFree;
    std::optional<IRFunctionReturnExpressionNode*> _returnExpression;
public:
    IRBlockNode(llvm::BasicBlock* irValue, IRBlockType type, IRLookupTable* scope);
    bool hasReturnStatement();
    bool hasBranchInstruction();
    bool hasReturnInstruction();
    IRLookupTable* getScope();
    llvm::BasicBlock* getBlock();
    std::vector<IRNode*>* getBody();
    void insert(IRNode* irNode);
    std::unique_ptr<llvm::IRBuilder<>>* getBuilder();
    void addVoidReturn();
    bool hasNodesToFree();
    bool hasVariablesToFree();
    void addExpressionToFree(IRExpressionNode* expressionNode);
    void addVariableToFree(IRVariableDeclarationNode* variableNode);
    void addLambdaVariableToFree(IRVariableDeclarationNode* variableNode);
    std::vector<IRNodeToFree*>* getNodesToFree();
    std::vector<IRExpressionNode*>* getExpressionsToFree();
    std::vector<IRVariableDeclarationNode*>* getVariablesToFree();
    std::vector<IRVariableDeclarationNode*>* getLambdaVariablesToFree();
    std::vector<IRNodeToFree*>* getAllNodesToFree();
    std::vector<IRExpressionNode*>* getAllExpressionsToFree();
    std::vector<IRVariableDeclarationNode*>* getAllVariablesToFree();
    std::vector<IRVariableDeclarationNode*>* getAllLambdaVariablesToFree();
    virtual void setInsertionPointBeforeLastInstruction();
    virtual void setInsertionPointBeforeFirstInstruction();
    virtual void resetInsertionPoint();
    virtual void removeLastInstruction();
    void transferNodesToFreeTo(IRBlockNode* other);
    void addReturnExpression(IRFunctionReturnExpressionNode* returnExpressionNode);
    std::optional<IRFunctionReturnExpressionNode*> getReturnExpression();
    void createSuccessor();
    std::vector<IRBlockNode*>* getSuccessors();
    std::set<IRBlockNode*>* getAllSuccessors();
    std::set<IRBlockNode*> getAllSuccessorsThatReturn();
    void addSuccessor(IRBlockNode* successorIrBlock);
    IRBlockNode* getLastSuccessorOrSelf();
    std::optional<IRBlockNode*> getParentBlock();
    bool is(IRBlockType blockType);
    bool isOneOf(std::vector<IRBlockType> blockTypes);
    void setParentBlock(IRBlockNode* parentIRBlock);
};

#endif //JETLANG_IR_BLOCK_NODE_H
