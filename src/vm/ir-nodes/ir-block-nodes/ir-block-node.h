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
    std::vector<IRBlockNode*> _childBlocks;
    std::vector<IRBlockNode*> _nestedBlocks;
    std::vector<IRBlockNode*> _successors;
    std::optional<IRBlockNode*> _parentBlock;
    std::optional<IRBlockNode*> _nestedParentBlock;
    std::vector<IRNodeToFree*> _nodesToFree;
    std::optional<IRFunctionReturnExpressionNode*> _returnExpression;
    bool _allowedToFreeNodes = true;
public:
    IRBlockNode(llvm::BasicBlock* irValue, IRBlockType type, IRLookupTable* scope);
    bool hasReturnStatement();
    bool hasBranchInstruction();
    bool hasReturnInstruction();
    bool isReachable();
    bool isUnreachable();
    bool isAllowedToFreeNodes();
    void preventFreeingNodes();
    IRLookupTable* getScope();
    llvm::BasicBlock* getBlock();
    std::vector<IRNode*>* getBody();
    void insert(IRNode* irNode);
    std::unique_ptr<llvm::IRBuilder<>>* getBuilder();
    void addVoidReturn();
    bool hasNodesToFree();
    void addExpressionToFree(IRExpressionNode* expressionNode, std::optional<IRBlockNode*> associatedIRBlock = {});
    void addVariableToFree(IRVariableDeclarationNode* variableNode, std::optional<IRBlockNode*> associatedIRBlock = {});
    void addLambdaVariableToFree(IRVariableDeclarationNode* variableNode, std::optional<IRBlockNode*> associatedIRBlock = {});
    std::vector<IRNodeToFree*>* getNodesToFree();
    std::vector<IRNodeToFree*> getNestedParentsNodesToFree();
    void setFinalBlockForNodesToFree(IRBlockNode* irBlock);
    virtual void setInsertionPointBeforeLastInstruction();
    virtual void setInsertionPointBeforeFirstInstruction();
    virtual void resetInsertionPoint();
    virtual void removeLastInstruction();
    void adoptNodesToFreeFrom(IRBlockNode* other);
    void addReturnExpression(IRFunctionReturnExpressionNode* returnExpressionNode);
    std::optional<IRFunctionReturnExpressionNode*> getReturnExpression();
    void createChild();
    std::vector<IRBlockNode*>* getSuccessors();
    std::set<IRBlockNode*>* getAllSuccessors();
    std::set<IRBlockNode*> getAllChildrenThatReturn();
    std::vector<IRBlockNode*>* getNestedBlocks();
    bool hasNestedBlocks();
    bool hasChildBlocks();
    void nest(IRBlockNode* irBlock);
    IRBlockNode* getLastChildOrSelf();
    std::optional<IRBlockNode*> getNestedParentBlock();
    bool is(IRBlockType blockType);
    bool isOneOf(std::vector<IRBlockType> blockTypes);
    void setParentBlock(IRBlockNode* parentIRBlock);
    void setNestedParentBlock(IRBlockNode* nestedParentIRBlock);
};

#endif //JETLANG_IR_BLOCK_NODE_H
