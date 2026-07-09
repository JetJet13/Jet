//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-primitive-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTPrimitiveTypeNode::ASTPrimitiveTypeNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTPrimitiveTypeNode::getLexeme() {
    return _lexeme;
}

std::shared_ptr<Position> ASTPrimitiveTypeNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

std::shared_ptr<Position> ASTPrimitiveTypeNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

ASTNodeType ASTPrimitiveTypeNode::getNodeType() {
    return AST_PRIMITIVE_TYPE_NODE;
}

std::string ASTPrimitiveTypeNode::toString() {
    return "PRIMITIVE_TYPE";
}

bool ASTPrimitiveTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTPrimitiveTypeNode>(other);
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTPrimitiveTypeNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}

std::string ASTPrimitiveTypeNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}