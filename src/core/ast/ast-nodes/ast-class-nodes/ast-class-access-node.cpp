//
// Created by Johny Georges on 2024-04-25.
//

#include "ast-class-access-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassAccessNode::ASTClassAccessNode(ASTThisNode* thisNode, ASTThisAccessNode* thisAccess) {
    _this = thisNode;
    _thisAccess = thisAccess;
    _children.push_back(_this);
    _children.push_back(_thisAccess);
}

ASTThisNode* ASTClassAccessNode::getThis() {
    return _this;
}

ASTThisAccessNode* ASTClassAccessNode::getThisAccess() {
    return _thisAccess;
}

ASTNodeType ASTClassAccessNode::getNodeType() {
    return AST_CLASS_ACCESS_NODE;
}

std::string ASTClassAccessNode::toString() {
    return "CLASS_ACCESS";
}

bool ASTClassAccessNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTClassAccessNode*)other;
    return this->getThis()->isSameAs(otherNode->getThis()) &&
           this->getThisAccess()->isSameAs(otherNode->getThisAccess());
}

void ASTClassAccessNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _this->print();
    _thisAccess->print();
    Logger::log("----------");
}

std::string ASTClassAccessNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_this)
    ->addWithWhitespace(_thisAccess);
    return sourceCodeBuilder.build();
}