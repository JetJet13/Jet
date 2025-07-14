//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-in-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTForInStatementNode::ASTForInStatementNode(ASTForNode* forKeyword, ASTForInVariableNode* variable, ASTForInNode* inKeyword, ASTForInSourceNode* source, ASTControlFlowBlockNode* block) {
    _forKeyword = forKeyword;
    _variable = variable;
    _inKeyword = inKeyword;
    _source = source;
    _block = block;
    _children.push_back(_forKeyword);
    _children.push_back(_variable);
    _children.push_back(_inKeyword);
    _children.push_back(_source);
    _children.push_back(_block);
}

ASTForInVariableNode* ASTForInStatementNode::getVariable() {
    return _variable;
}

ASTForInSourceNode* ASTForInStatementNode::getSource() {
    return _source;
}

ASTControlFlowBlockNode* ASTForInStatementNode::getBlock() {
    return _block;
}

Position* ASTForInStatementNode::getStartPosition() {
    return _forKeyword->getStartPosition();
}

Position* ASTForInStatementNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTForInStatementNode::getNodeType() {
    return AST_FOR_IN_STATEMENT_NODE;
}

std::string ASTForInStatementNode::toString() {
    return "FOR_IN_STATEMENT";
}

bool ASTForInStatementNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTForInStatementNode*)other;

    return  this->getVariable()->isSameAs(otherNode->getVariable()) &&
            this->getSource()->isSameAs(otherNode->getSource()) &&
            this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTForInStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _variable->print();
    _source->print();
    _block->print();
    Logger::log("----------");
}

std::string ASTForInStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_forKeyword)
    ->add(_variable)
    ->add(_inKeyword)
    ->add(_source)
    ->add(_block);
    return sourceCodeBuilder.build();
}