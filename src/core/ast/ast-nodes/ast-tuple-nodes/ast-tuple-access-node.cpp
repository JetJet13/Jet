//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-access-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTupleAccessNode::ASTTupleAccessNode(std::shared_ptr<Lexeme> lexeme) {
    _lexeme = lexeme;
}

std::shared_ptr<Lexeme> ASTTupleAccessNode::getLexeme() {
    return _lexeme;
}

std::shared_ptr<Position> ASTTupleAccessNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

std::shared_ptr<Position> ASTTupleAccessNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

ASTNodeType ASTTupleAccessNode::getNodeType() {
    return AST_TUPLE_ACCESS_NODE;
}

std::string ASTTupleAccessNode::toString() {
    return "TUPLE_ACCESS";
}

bool ASTTupleAccessNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTupleAccessNode>(other);
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTTupleAccessNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}

std::string ASTTupleAccessNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}

std::shared_ptr<ASTTupleAccessNode> ASTTupleAccessNode::setIndexValue(std::string index) {
    _index = std::stoll(index);
    return std::dynamic_pointer_cast<ASTTupleAccessNode>(shared_from_this());
}

int64_t ASTTupleAccessNode::getIndexValue() {
    return _index;
}