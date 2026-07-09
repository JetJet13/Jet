//
// Created by Johny Georges on 2024-04-10.
//

#include "ast-variable-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTVariableDefinitionNode::ASTVariableDefinitionNode(std::shared_ptr<ASTVariableTypeNode> assignmentTypeQualifier, std::shared_ptr<ASTIdentifierNode> astIdentifierNode) {
    _assignmentTypeQualifier = assignmentTypeQualifier;
    _identifier = astIdentifierNode;
    _children.push_back(_assignmentTypeQualifier);
    _children.push_back(_identifier);
}

std::shared_ptr<ASTVariableTypeNode> ASTVariableDefinitionNode::getVarTypeNode() {
    return _assignmentTypeQualifier;
}

std::shared_ptr<ASTIdentifierNode> ASTVariableDefinitionNode::getIdentifierNode() {
    return _identifier;
}

std::shared_ptr<Position> ASTVariableDefinitionNode::getStartPosition() {
    return _assignmentTypeQualifier->getStartPosition();
}

std::shared_ptr<Position> ASTVariableDefinitionNode::getEndPosition() {
    return _identifier->getEndPosition();
}

ASTNodeType ASTVariableDefinitionNode::getNodeType() {
    return AST_VARIABLE_DEFINITION_NODE;
}

std::string ASTVariableDefinitionNode::toString() {
    return "VARIABLE_DEFINITION";
}

bool ASTVariableDefinitionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTVariableDefinitionNode>(other);

    return this->getVarTypeNode()->isSameAs(otherNode->getVarTypeNode()) &&
           this->getIdentifierNode()->isSameAs(otherNode->getIdentifierNode());
}

void ASTVariableDefinitionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _assignmentTypeQualifier->print();
    _identifier->print();
    Logger::log("----------");
}

std::string ASTVariableDefinitionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_assignmentTypeQualifier)->add(_identifier);
    return sourceCodeBuilder.build();
}