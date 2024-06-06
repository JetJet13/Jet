//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTForStatementNode::ASTForStatementNode(ASTForNode* forKeyword, ASTForVariableNode* variable, ASTForInNode* inKeyword, ASTForSourceNode* source, ASTControlFlowBlockNode* block) {
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

ASTForVariableNode* ASTForStatementNode::getVariable() {
    return _variable;
}

ASTForSourceNode* ASTForStatementNode::getSource() {
    return _source;
}

ASTControlFlowBlockNode* ASTForStatementNode::getBlock() {
    return _block;
}

Position* ASTForStatementNode::getStartPosition() {
    return _forKeyword->getStartPosition();
}

Position* ASTForStatementNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTForStatementNode::getNodeType() {
    return AST_FOR_STATEMENT_NODE;
}

std::string ASTForStatementNode::toString() {
    return "FOR_STATEMENT";
}

bool ASTForStatementNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTForStatementNode*)other;

    return  this->getVariable()->isSameAs(otherNode->getVariable()) &&
            this->getSource()->isSameAs(otherNode->getSource()) &&
            this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTForStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _variable->print();
    _source->print();
    _block->print();
    Logger::log("----------");
}

std::string ASTForStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_forKeyword)
    ->addWithWhitespace(_variable)
    ->addWithWhitespace(_inKeyword)
    ->addWithWhitespace(_source)
    ->addWithWhitespace(_block);
    return sourceCodeBuilder.build();
}