//
// Created by Johny Georges on 2024-04-10.
//

#include "ast-variable-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTVariableDefinitionNode::ASTVariableDefinitionNode(ASTVariableTypeNode* assignmentTypeQualifier, ASTIdentifierNode* astIdentifierNode) {
    _assignmentTypeQualifier = assignmentTypeQualifier;
    _identifier = astIdentifierNode;
    _children.push_back(_assignmentTypeQualifier);
    _children.push_back(_identifier);
}

ASTVariableTypeNode* ASTVariableDefinitionNode::getVarTypeNode() {
    return _assignmentTypeQualifier;
}

ASTIdentifierNode* ASTVariableDefinitionNode::getIdentifierNode() {
    return _identifier;
}

ASTNodeType ASTVariableDefinitionNode::getNodeType() {
    return AST_VARIABLE_DEFINITION_NODE;
}

std::string ASTVariableDefinitionNode::toString() {
    return "VARIABLE_DEFINITION";
}

bool ASTVariableDefinitionNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTVariableDefinitionNode*)other;

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
    sourceCodeBuilder.add(_assignmentTypeQualifier)->addWithWhitespace(_identifier);
    return sourceCodeBuilder.build();
}