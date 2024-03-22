//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-procedure-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTProcedureNode::ASTProcedureNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTProcedureNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTProcedureNode::getNodeType() {
    return AST_PROCEDURE_NODE;
}

std::string ASTProcedureNode::toString() {
    return "PROCEDURE";
}

bool ASTProcedureNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTProcedureNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTProcedureNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}