//
// Created by Johny Georges on 2024-03-07.
//

#include "ast-group-end-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-function-nodes/ast-function-parameter-list-end-node.h"
#include "../../../pre-processor/syntax-analyzer/types/syntax-analyzer-mode.h"
#include "../ast-function-nodes/ast-function-argument-list-end-node.h"
#include "../ast-tuple-nodes/ast-tuple-list-end-node.h"

ASTGroupEndNode::ASTGroupEndNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTGroupEndNode::getLexeme() {
    return _lexeme;
}

ASTNode* ASTGroupEndNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_FUNCTION_PARAMETER_LIST_MODE) {
        return new ASTFunctionParameterListEndNode(this->getLexeme());
    }

    if (nextNode && nextNode.value()->isOneOf({ AST_FAT_ARROW_NODE })) {
        return new ASTFunctionParameterListEndNode(this->getLexeme());
    }

    if (mode == SA_FUNCTION_ARGUMENT_LIST_MODE) {
        return new ASTFunctionArgumentListEndNode(this->getLexeme());
    }

    return this;
}

ASTNodeType ASTGroupEndNode::getNodeType() {
    return AST_GROUP_END_NODE;
}

std::string ASTGroupEndNode::toString() {
    return "GROUP_END";
}

bool ASTGroupEndNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTGroupEndNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTGroupEndNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}