//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-block-node.h"
#include "../../../shared/utils/logger/logger.h"

IRBlockNode::IRBlockNode(llvm::BasicBlock* irValue, IRBlockType type, IRLookupTable* scope) {
    _irValue = irValue;
    _type = type;
    _scope = scope;
    _builder = std::make_unique<llvm::IRBuilder<>>(_irValue);
    _nodesToFree = std::vector<IRNodeToFree*>();
}

bool IRBlockNode::hasReturnStatement() {
    if (_body.empty()) {
        return false;
    }
    return _body.back()->is(IR_FUNCTION_RETURN_EXPRESSION_NODE);
}

bool IRBlockNode::hasBranchInstruction() {
    if (_irValue->getTerminator()) {
        return llvm::isa<llvm::BranchInst>(_irValue->getTerminator());
    }
    return false;
}

bool IRBlockNode::hasReturnInstruction() {
    if (_irValue->getTerminator()) {
        return llvm::isa<llvm::ReturnInst>(_irValue->getTerminator());
    }
    return false;
}

bool IRBlockNode::isReachable() {
    auto isEntryBlock = &_irValue->getParent()->getEntryBlock() == _irValue;
    auto hasOneOrMorePredecessors = _irValue->hasNPredecessorsOrMore(1);
    return isEntryBlock || hasOneOrMorePredecessors;
}

bool IRBlockNode::isUnreachable() {
    return !this->isReachable();
}

IRLookupTable* IRBlockNode::getScope() {
    return _scope;
}

llvm::BasicBlock* IRBlockNode::getBlock() {
    return _irValue;
}

std::vector<IRNode*>* IRBlockNode::getBody() {
    return &_body;
}

void IRBlockNode::insert(IRNode* irNode) {
    _body.push_back(irNode);
}

std::unique_ptr<llvm::IRBuilder<>>* IRBlockNode::getBuilder() {
    return &_builder;
}

void IRBlockNode::addVoidReturn() {
    _builder.get()->CreateRetVoid();
}

bool IRBlockNode::hasNodesToFree() {
    return _nodesToFree.size() > 0;
}

bool IRBlockNode::hasVariablesToFree() {
    return this->getVariablesToFree()->size() > 0;
}

void IRBlockNode::transferNodesToFreeTo(IRBlockNode* other) {
    other->getNodesToFree()->insert(other->getNodesToFree()->begin(), _nodesToFree.begin(), _nodesToFree.end());
    other->getVariablesToFree()->insert(other->getVariablesToFree()->begin(), _variablesToFree.begin(), _variablesToFree.end());
    other->getExpressionsToFree()->insert(other->getExpressionsToFree()->begin(), _expressionsToFree.begin(), _expressionsToFree.end());
    other->getLambdaVariablesToFree()->insert(other->getLambdaVariablesToFree()->begin(), _lambdaVariablesToFree.begin(), _lambdaVariablesToFree.end());
    _nodesToFree.clear();
    _variablesToFree.clear();
    _expressionsToFree.clear();
    _lambdaVariablesToFree.clear();
}

void IRBlockNode::addReturnExpression(IRFunctionReturnExpressionNode* returnExpressionNode) {
    _returnExpression = returnExpressionNode;
}

void IRBlockNode::addExpressionToFree(IRExpressionNode* expressionNode) {
    _expressionsToFree.insert(_expressionsToFree.begin(), expressionNode);
    _nodesToFree.insert(_nodesToFree.begin(), new IRNodeToFree(expressionNode, this));
}

void IRBlockNode::addVariableToFree(IRVariableDeclarationNode* variableNode) {
    _variablesToFree.insert(_variablesToFree.begin(), variableNode);
    _nodesToFree.insert(_nodesToFree.begin(), new IRNodeToFree(variableNode, this));
}

void IRBlockNode::addLambdaVariableToFree(IRVariableDeclarationNode* variableNode) {
    _lambdaVariablesToFree.insert(_lambdaVariablesToFree.begin(), variableNode);
    _nodesToFree.insert(_nodesToFree.begin(), new IRNodeToFree(variableNode, this));
}

std::vector<IRNodeToFree*>* IRBlockNode::getNodesToFree() {
    return &_nodesToFree;
}

std::vector<IRExpressionNode*>* IRBlockNode::getExpressionsToFree() {
    return &_expressionsToFree;
}

std::vector<IRVariableDeclarationNode*>* IRBlockNode::getVariablesToFree() {
    return &_variablesToFree;
}

std::vector<IRVariableDeclarationNode*>* IRBlockNode::getLambdaVariablesToFree() {
    return &_lambdaVariablesToFree;
}

std::vector<IRNodeToFree*>* IRBlockNode::getAllNodesToFree() {
    auto allNodesToFree = new std::vector<IRNodeToFree*>();
    allNodesToFree->insert(allNodesToFree->begin(), _nodesToFree.begin(), _nodesToFree.end());
    for (auto successorBlock : _successors) {
        if (successorBlock->is(IR_BASIC_BT)) {
            auto moreNodesToFree = successorBlock->getAllNodesToFree();
            allNodesToFree->insert(
                    allNodesToFree->begin(),
                    moreNodesToFree->begin(),
                    moreNodesToFree->end()
            );

        }
    }
    return allNodesToFree;
}

std::vector<IRExpressionNode*>* IRBlockNode::getAllExpressionsToFree() {
    auto allExpressionsToFree = new std::vector<IRExpressionNode*>();
    allExpressionsToFree->insert(allExpressionsToFree->begin(), _expressionsToFree.begin(), _expressionsToFree.end());
    for (auto successorBlock : _successors) {
        if (successorBlock->is(IR_BASIC_BT)) {
            auto moreExpressionsToFree = successorBlock->getAllExpressionsToFree();
            allExpressionsToFree->insert(
                    allExpressionsToFree->begin(),
                    moreExpressionsToFree->begin(),
                    moreExpressionsToFree->end()
            );

        }
    }
    return allExpressionsToFree;
}

std::vector<IRVariableDeclarationNode*>* IRBlockNode::getAllVariablesToFree() {
    auto allVariablesToFree = new std::vector<IRVariableDeclarationNode*>();
    allVariablesToFree->insert(allVariablesToFree->begin(), _variablesToFree.begin(), _variablesToFree.end());
    for (auto successorBlock : _successors) {
        if (successorBlock->is(IR_BASIC_BT)) {
            auto moreVariablesToFree = successorBlock->getAllVariablesToFree();
            allVariablesToFree->insert(
                    allVariablesToFree->begin(),
                    moreVariablesToFree->begin(),
                    moreVariablesToFree->end()
            );

        }
    }
    return allVariablesToFree;
}

std::vector<IRVariableDeclarationNode*>* IRBlockNode::getAllLambdaVariablesToFree() {
    auto allLambdaVariablesToFree = new std::vector<IRVariableDeclarationNode*>();
    allLambdaVariablesToFree->insert(allLambdaVariablesToFree->begin(), _lambdaVariablesToFree.begin(), _lambdaVariablesToFree.end());
    for (auto successorBlock : _successors) {
        if (successorBlock->is(IR_BASIC_BT)) {
            auto moreLambdaVariablesToFree = successorBlock->getAllLambdaVariablesToFree();
            allLambdaVariablesToFree->insert(
                allLambdaVariablesToFree->begin(),
                moreLambdaVariablesToFree->begin(),
                moreLambdaVariablesToFree->end()
            );
        }
    }
    return allLambdaVariablesToFree;
}

std::optional<IRFunctionReturnExpressionNode*> IRBlockNode::getReturnExpression() {
    return _returnExpression;
}

void IRBlockNode::setInsertionPointBeforeLastInstruction() {
    auto block = this->getLastSuccessorOrSelf();
    if (block->getBlock()->getTerminator()) {
        block->getBuilder()->get()->SetInsertPoint(block->getBlock()->getTerminator());
    }
}

void IRBlockNode::setInsertionPointBeforeFirstInstruction() {
    this->getBuilder()->get()->SetInsertPoint(&*this->getBlock()->getFirstInsertionPt());
}

void IRBlockNode::resetInsertionPoint() {
    auto block = this->getLastSuccessorOrSelf();
    block->getBuilder()->get()->SetInsertPoint(block->getBlock());
}

void IRBlockNode::removeLastInstruction() {
    if (this->getBlock()->getTerminator()) {
        this->getBlock()->getTerminator()->eraseFromParent();
        this->getBuilder()->get()->SetInsertPoint(this->getBlock());
    }
}

void IRBlockNode::createSuccessor() {
    auto newBlock = new IRBlockNode(
        llvm::BasicBlock::Create(this->getBlock()->getContext(), "", this->getBlock()->getParent()),
        IR_BASIC_BT,
        _scope
    );
    newBlock->setParentBlock(this);
    _successors.push_back(newBlock);
}

std::vector<IRBlockNode*>* IRBlockNode::getSuccessors() {
    return &_successors;
}

std::set<IRBlockNode*>* IRBlockNode::getAllSuccessors() {
    auto allSuccessors = new std::set<IRBlockNode*>();
    for (auto successor : _successors) {
        allSuccessors->insert(successor);
        auto successorsOfSuccessor = successor->getAllSuccessors();
        allSuccessors->insert(successorsOfSuccessor->begin(), successorsOfSuccessor->end());
    }
    return allSuccessors;
}

std::set<IRBlockNode*> IRBlockNode::getAllSuccessorsThatReturn() {
    auto allSuccessorsThatReturn = std::set<IRBlockNode*>();
    for (auto successor : _successors) {
        if (successor->hasReturnInstruction()) {
            allSuccessorsThatReturn.insert(successor);
        }
        auto successorsThatReturnOfSuccessor = successor->getAllSuccessorsThatReturn();
        allSuccessorsThatReturn.insert(successorsThatReturnOfSuccessor.begin(), successorsThatReturnOfSuccessor.end());
    }
    if (this->hasReturnInstruction()) {
        allSuccessorsThatReturn.insert(this->getLastSuccessorOrSelf());
    }
    return allSuccessorsThatReturn;
}

void IRBlockNode::addSuccessor(IRBlockNode* successorIrBlock) {
    _successors.push_back(successorIrBlock);
    successorIrBlock->setParentBlock(this);
    auto successorsOfSuccessorIrBlock = successorIrBlock->getSuccessors();
    for (unsigned long i = 0; i < successorsOfSuccessorIrBlock->size(); ++i) {
        _successors.push_back(successorsOfSuccessorIrBlock->at(i));
        successorsOfSuccessorIrBlock->at(i)->setParentBlock(this);
    }
}

IRBlockNode* IRBlockNode::getLastSuccessorOrSelf() {
    if (_successors.empty()) {
        return this;
    }
    return _successors.back();
}

std::optional<IRBlockNode*> IRBlockNode::getParentBlock() {
    return _parentBlock;
}

bool IRBlockNode::is(IRBlockType blockType) {
    return _type == blockType;
}

bool IRBlockNode::isOneOf(std::vector<IRBlockType> blockTypes) {
    return std::find(
            blockTypes.begin(),
            blockTypes.end(),
            _type) != blockTypes.end();
}

void IRBlockNode::setParentBlock(IRBlockNode* parentIRBlock) {
    _parentBlock = parentIRBlock;
}