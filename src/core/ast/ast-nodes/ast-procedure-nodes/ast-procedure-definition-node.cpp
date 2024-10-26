//
// Created by Johny Georges on 2024-10-25.
//

#include "ast-procedure-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTProcedureDefinitionNode::ASTProcedureDefinitionNode(ASTProcedureNode* functionKeyword, ASTFunctionNameNode* name, ASTFunctionParameterListNode* parameters) {
    _procedureKeyword = functionKeyword;
    _name = name;
    _parameters = parameters;
    _children.push_back(_procedureKeyword);
    _children.push_back(_name);
    _children.push_back(_parameters);
}

ASTFunctionParameterListNode* ASTProcedureDefinitionNode::getParameters() {
    return _parameters;
}

ASTFunctionNameNode* ASTProcedureDefinitionNode::getName() {
    return _name;
}

unsigned long ASTProcedureDefinitionNode::numParameters() {
    return _parameters->numParameters();
}

Position* ASTProcedureDefinitionNode::getStartPosition() {
    return _procedureKeyword->getStartPosition();
}

Position* ASTProcedureDefinitionNode::getEndPosition() {
    return _parameters->getEndPosition();
}

ASTNodeType ASTProcedureDefinitionNode::getNodeType() {
    return AST_PROCEDURE_DEFINITION_NODE;
}

std::string ASTProcedureDefinitionNode::toString() {
    return "PROCEDURE_DEFINITION";
}

bool ASTProcedureDefinitionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTProcedureDefinitionNode*)other;

    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getParameters()->isSameAs(otherNode->getParameters());
}

void ASTProcedureDefinitionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _parameters->print();
    Logger::log("----------");
}

std::string ASTProcedureDefinitionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_procedureKeyword);
    sourceCodeBuilder.addWithWhitespace(_name)
    ->addWithWhitespace(_parameters);
    return sourceCodeBuilder.build();
}