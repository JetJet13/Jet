//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-variable-init-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTVariableInitNode::ASTVariableInitNode(ASTVariableTypeNode* assignmentTypeQualifier, ASTIdentifierNode* astIdentifierNode, ASTAssignmentOperatorNode* assignmentOperator, std::optional<ASTTypeColonNode*> colon, std::optional<ASTTypeNode*> type) {
    _assignmentTypeQualifier = assignmentTypeQualifier;
    _identifier = astIdentifierNode;
    _colon = colon;
    _type = type;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_assignmentTypeQualifier);
    _children.push_back(_identifier);
    if (_type) {
        _children.push_back(_type.value());
    }
}

ASTVariableTypeNode* ASTVariableInitNode::getVarTypeNode() {
    return _assignmentTypeQualifier;
}

ASTIdentifierNode* ASTVariableInitNode::getIdentifierNode() {
    return _identifier;
}

std::optional<ASTTypeNode*> ASTVariableInitNode::getTypeNode() {
    return _type;
}

Position* ASTVariableInitNode::getStartPosition() {
    return _assignmentTypeQualifier->getStartPosition();
}

Position* ASTVariableInitNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTVariableInitNode::getNodeType() {
    return AST_VARIABLE_INIT_NODE;
}

std::string ASTVariableInitNode::toString() {
    return "VARIABLE_INIT";
}

bool ASTVariableInitNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTVariableInitNode*)other;

    if (!_type.has_value() && otherNode->getTypeNode().has_value() ||
            _type.has_value() && !otherNode->getTypeNode().has_value()) {
        return false;
    }

    if (_type.has_value() && otherNode->getTypeNode().has_value() &&
        !_type.value()->isSameAs(otherNode->getTypeNode().value())) {
        return false;
    }

    return this->getVarTypeNode()->isSameAs(otherNode->getVarTypeNode()) &&
           this->getIdentifierNode()->isSameAs(otherNode->getIdentifierNode());
}

void ASTVariableInitNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _assignmentTypeQualifier->print();
    _identifier->print();
    if (_type) {
        _type.value()->print();
    }
    Logger::log("----------");
}

std::string ASTVariableInitNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_assignmentTypeQualifier)->add(_identifier);

    if (_colon && _type) {
        sourceCodeBuilder.add(_colon.value())->add(_type.value());
    }
    sourceCodeBuilder.add(_assignmentOperator);
    return sourceCodeBuilder.build();
}