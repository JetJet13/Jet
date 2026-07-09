//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-block-node.h"
#include "../../../shared/utils/logger/logger.h"

IRBlockNode::IRBlockNode(llvm::BasicBlock* irValue, IRBlockType type, std::shared_ptr<IRLookupTable> scope) {
    _irValue = irValue;
    _type = type;
    _scope = scope;
    _builder = std::make_unique<llvm::IRBuilder<>>(_irValue);
    _nodesToFree = std::vector<std::shared_ptr<IRNodeToFree>>();
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

bool IRBlockNode::isAllowedToFreeNodes() {
    return _allowedToFreeNodes;
}

void IRBlockNode::preventFreeingNodes() {
    _allowedToFreeNodes = false;
}

std::shared_ptr<IRBlockNode> IRBlockNode::markAsFakeBlock() {
    _representsRealBlock = false;
    return shared_from_this();
}

std::shared_ptr<IRLookupTable> IRBlockNode::getScope() {
    return _scope;
}

llvm::BasicBlock* IRBlockNode::getBlock() {
    return _irValue;
}

std::vector<std::shared_ptr<IRNode>>* IRBlockNode::getBody() {
    return &_body;
}

void IRBlockNode::insert(std::shared_ptr<IRNode> irNode) {
    _body.push_back(irNode);
}

std::unique_ptr<llvm::IRBuilder<>>* IRBlockNode::getBuilder() {
    return &_builder;
}

void IRBlockNode::addVoidReturn() {
    _builder.get()->CreateRetVoid();
}

bool IRBlockNode::hasNodesToFree() {
    return !_nodesToFree.empty();
}

void IRBlockNode::adoptNodesToFreeFrom(std::shared_ptr<IRBlockNode> other) {
    if (_parentBlock) {
        _parentBlock.value()->adoptNodesToFreeFrom(other);
        return;
    }
    auto otherNodesToFree = other->getNodesToFree();
    _nodesToFree.insert(_nodesToFree.end(), otherNodesToFree->begin(), otherNodesToFree->end());
}

void IRBlockNode::addReturnExpression(std::shared_ptr<IRFunctionReturnExpressionNode> returnExpressionNode) {
    _returnExpression = returnExpressionNode;
}

void IRBlockNode::addExpressionToFree(std::shared_ptr<IRExpressionNode> expressionNode, std::optional<std::shared_ptr<IRBlockNode>> associatedIRBlock) {
    if (_parentBlock) {
        _parentBlock.value()->addExpressionToFree(expressionNode, shared_from_this());
        return;
    }
    _nodesToFree.insert(_nodesToFree.begin(), std::make_shared<IRNodeToFree>(expressionNode, associatedIRBlock.value_or(shared_from_this())));
}

void IRBlockNode::addVariableToFree(std::shared_ptr<IRVariableDeclarationNode> variableNode, std::optional<std::shared_ptr<IRBlockNode>> associatedIRBlock) {
    if (_parentBlock) {
        _parentBlock.value()->addVariableToFree(variableNode, associatedIRBlock.value_or(shared_from_this()));
        return;
    }
    _nodesToFree.insert(_nodesToFree.begin(), std::make_shared<IRNodeToFree>(variableNode, associatedIRBlock.value_or(shared_from_this())));
}

void IRBlockNode::addLambdaVariableToFree(std::shared_ptr<IRVariableDeclarationNode> variableNode, std::optional<std::shared_ptr<IRBlockNode>> associatedIRBlock) {
    if (_parentBlock) {
        _parentBlock.value()->addLambdaVariableToFree(variableNode, associatedIRBlock.value_or(shared_from_this()));
        return;
    }
    _nodesToFree.insert(_nodesToFree.begin(), std::make_shared<IRNodeToFree>(variableNode, associatedIRBlock.value_or(shared_from_this())));
}

std::vector<std::shared_ptr<IRNodeToFree>>* IRBlockNode::getNodesToFree() {
    return &_nodesToFree;
}

std::vector<std::shared_ptr<IRNodeToFree>> IRBlockNode::getNestedParentsNodesToFree() {
    if (!_nestedParentBlock) {
        return std::vector<std::shared_ptr<IRNodeToFree>>();
    }

    auto nodesToFree = std::vector<std::shared_ptr<IRNodeToFree>>();
    auto nestedParentBlock = _nestedParentBlock;
    while (nestedParentBlock) {
        auto nestedNodesToFree = nestedParentBlock.value()->getNodesToFree();
        nodesToFree.insert(nodesToFree.end(), nestedNodesToFree->begin(), nestedNodesToFree->end());
        nestedParentBlock = nestedParentBlock.value()->getNestedParentBlock();
    }
    return nodesToFree;
}

void IRBlockNode::setFinalBlockForNodesToFree(std::shared_ptr<IRBlockNode> irBlock) {
    for (auto nodeToFree : _nodesToFree) {
        nodeToFree->setFinalBlockToFree(irBlock);
    }
}

std::optional<std::shared_ptr<IRFunctionReturnExpressionNode>> IRBlockNode::getReturnExpression() {
    return _returnExpression;
}

void IRBlockNode::setInsertionPointBeforeLastInstruction() {
    auto block = this->getLastChildOrSelf();
    if (block->getBlock()->getTerminator()) {
        block->getBuilder()->get()->SetInsertPoint(block->getBlock()->getTerminator());
    }
}

void IRBlockNode::setInsertionPointBeforeFirstInstruction() {
    this->getBuilder()->get()->SetInsertPoint(&*this->getBlock()->getFirstInsertionPt());
}

void IRBlockNode::resetInsertionPoint() {
    auto block = this->getLastChildOrSelf();
    block->getBuilder()->get()->SetInsertPoint(block->getBlock());
}

void IRBlockNode::removeLastInstruction() {
    if (this->getBlock()->getTerminator()) {
        this->getBlock()->getTerminator()->eraseFromParent();
        this->getBuilder()->get()->SetInsertPoint(this->getBlock());
    }
}

void IRBlockNode::createChild() {
    auto newBlock = std::make_shared<IRBlockNode>(
        llvm::BasicBlock::Create(this->getBlock()->getContext(), "", this->getBlock()->getParent()),
        IR_BASIC_BT,
        _scope
    );
    newBlock->setParentBlock(shared_from_this());
    _childBlocks.push_back(newBlock);
    _successors.push_back(newBlock);
}

std::vector<std::shared_ptr<IRBlockNode>>* IRBlockNode::getSuccessors() {
    return &_successors;
}

std::shared_ptr<std::set<std::shared_ptr<IRBlockNode>>> IRBlockNode::getAllSuccessors() {
    auto allSuccessors = std::make_shared<std::set<std::shared_ptr<IRBlockNode>>>();
    for (auto successor : _successors) {
        allSuccessors->insert(successor);
        auto successorsOfSuccessor = successor->getAllSuccessors();
        allSuccessors->insert(successorsOfSuccessor->begin(), successorsOfSuccessor->end());
    }
    return allSuccessors;
}

std::set<std::shared_ptr<IRBlockNode>> IRBlockNode::getAllChildrenThatReturn() {
    auto allChildrenThatReturn = std::set<std::shared_ptr<IRBlockNode>>();
    for (auto childBlock : _childBlocks) {
        if (childBlock->hasReturnInstruction()) {
            allChildrenThatReturn.insert(childBlock);
        }
    }
    if (this->hasReturnInstruction()) {
        allChildrenThatReturn.insert(shared_from_this());
    }
    return allChildrenThatReturn;
}

std::vector<std::shared_ptr<IRBlockNode>>* IRBlockNode::getNestedBlocks() {
    return &_nestedBlocks;
}

bool IRBlockNode::hasNestedBlocks() {
    return !_nestedBlocks.empty();
}

bool IRBlockNode::allImmediateNestedBlocksReturn() {
    for (auto nestedBlock : _nestedBlocks) {
        if (nestedBlock->getNestedParentBlock() != shared_from_this()) {
            continue;
        }
        if (nestedBlock->canReturn() && !nestedBlock->getLastChildOrSelf()->hasReturnInstruction()) {
            return false;
        }
    }
    return true;
}

void IRBlockNode::nest(std::shared_ptr<IRBlockNode> irBlock) {
    _nestedBlocks.push_back(irBlock);
    irBlock->setNestedParentBlock(shared_from_this());
    _successors.push_back(irBlock);

    auto nestedOfNestedIrBlock = irBlock->getNestedBlocks();
    for (unsigned long i = 0; i < nestedOfNestedIrBlock->size(); ++i) {
        auto block = nestedOfNestedIrBlock->at(i);
        _nestedBlocks.push_back(block);
    }

    auto successorsOfSuccessorIrBlock = irBlock->getSuccessors();
    for (unsigned long i = 0; i < successorsOfSuccessorIrBlock->size(); ++i) {
        auto block = successorsOfSuccessorIrBlock->at(i);
        _successors.push_back(block);
    }
}

std::shared_ptr<IRBlockNode> IRBlockNode::getLastChildOrSelf() {
    if (_childBlocks.empty()) {
        return shared_from_this();
    }
    return _childBlocks.back();
}

std::optional<std::shared_ptr<IRBlockNode>> IRBlockNode::getNestedParentBlock() {
    if (_parentBlock) {
        return _parentBlock.value()->getNestedParentBlock();
    }
    return _nestedParentBlock;
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

bool IRBlockNode::canReturn() {
    return _representsRealBlock && this->isOneOf({
        IR_BASIC_BT,
        IR_IF_THEN_BT,
        IR_IF_ELSE_BT,
        IR_WHILE_BODY_BT,
        IR_FOR_LOOP_BODY_BT,
        IR_FOR_IN_BODY_BT
    });
}

bool IRBlockNode::isEntryBlock() {
    return _irValue == &_irValue->getParent()->getEntryBlock();
}

void IRBlockNode::setParentBlock(std::shared_ptr<IRBlockNode> parentIRBlock) {
    _parentBlock = parentIRBlock;
}

void IRBlockNode::setNestedParentBlock(std::shared_ptr<IRBlockNode> nestedParentIRBlock) {
    _nestedParentBlock = nestedParentIRBlock;
}