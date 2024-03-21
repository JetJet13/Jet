//
// Created by Johny Georges on 2024-03-07.
//

#include "ast-group-start-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-function-nodes/ast-function-parameter-list-start-node.h"

ASTGroupStartNode::ASTGroupStartNode(Lexeme *lexeme) {
_lexeme = lexeme;
}

Lexeme* ASTGroupStartNode::getLexeme() {
    return _lexeme;
}

ASTNode* ASTGroupStartNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, HandleMode mode) {
    if (prevNode && prevNode.value()->is(AST_FUNCTION_NAME_NODE)) {
        return new ASTFunctionParameterListStartNode(this->getLexeme());
    }
    return this;
}

ASTNodeType ASTGroupStartNode::getNodeType() {
    return AST_GROUP_START_NODE;
}

std::string ASTGroupStartNode::toString() {
    return "GROUP_START";
}

bool ASTGroupStartNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTGroupStartNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTGroupStartNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}