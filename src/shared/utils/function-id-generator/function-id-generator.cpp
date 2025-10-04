//
// Created by Johny Georges on 2025-08-02.
//

#include "function-id-generator.h"
#include "../md5/md5.h"
#include "../logger/logger.h"

std::string FunctionIdGenerator::getNameFromId(std::string functionId) {
    auto periodAndMd5HashLength = 33;
    return functionId.substr(0, functionId.size() - periodAndMd5HashLength);
}

std::string FunctionIdGenerator::generateFor(ASTClassMethodDeclarationNode* classMethodDeclarationNode) {
    auto id = classMethodDeclarationNode->getId()
              + "."
              + MD5().operator()(classMethodDeclarationNode->getTypeSignature()->toDetailString());
    return id;
}

std::string FunctionIdGenerator::generateFor(ASTFunctionDeclarationNode* functionDeclarationNode) {
    auto id = functionDeclarationNode->getId()
              + "."
              + MD5().operator()(functionDeclarationNode->getTypeSignature()->toDetailString());
    return id;
}

std::string FunctionIdGenerator::generateFor(ASTProcedureDeclarationNode* procedureDeclarationNode) {
    auto id = procedureDeclarationNode->getId()
              + "."
              + MD5().operator()(procedureDeclarationNode->getTypeSignature()->toDetailString());
    return id;
}

std::string FunctionIdGenerator::generateFor(ASTFunctionInvocationExpressionNode* functionInvocationExpressionNode) {
    auto id = functionInvocationExpressionNode->getFunction()->getId() + "."
              + MD5().operator()(functionInvocationExpressionNode->getArguments()->getTypeSignature()->toDetailString());
    return id;
}

std::string FunctionIdGenerator::generateFor(ASTObjectAccessInvocationExpressionNode* objectAccessInvocationExpressionNode) {
    auto id = objectAccessInvocationExpressionNode->getName() + "."
              + MD5().operator()(objectAccessInvocationExpressionNode->getArguments()->getTypeSignature()->toDetailString());
    return id;
}

std::string FunctionIdGenerator::generateFor(std::string functionName, std::string parameterDetailString) {
    auto id = functionName + "." + MD5().operator()(parameterDetailString);
    return id;
}