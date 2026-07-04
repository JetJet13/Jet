//
// Created by Johny Georges on 2025-08-02.
//

#include "function-id-generator.h"
#include "../md5/md5.h"
#include "../logger/logger.h"

std::string FunctionIdGenerator::getNameFromId(std::string functionId) {
    auto delimiterIndex = functionId.find('.');
    return functionId.substr(0, delimiterIndex);
}

std::string FunctionIdGenerator::generateFor(std::shared_ptr<ASTClassMethodDeclarationNode> classMethodDeclarationNode) {
    auto id = classMethodDeclarationNode->getId()
              + "."
              + MD5().operator()(classMethodDeclarationNode->getTypeSignature()->toDetailString());
    return id;
}

std::string FunctionIdGenerator::generateFor(std::shared_ptr<ASTFunctionDeclarationNode> functionDeclarationNode) {
    auto id = functionDeclarationNode->getId()
              + "."
              + MD5().operator()(functionDeclarationNode->getTypeSignature()->toDetailString());
    return id;
}

std::string FunctionIdGenerator::generateFor(std::shared_ptr<ASTProcedureDeclarationNode> procedureDeclarationNode) {
    auto id = procedureDeclarationNode->getId()
              + "."
              + MD5().operator()(procedureDeclarationNode->getTypeSignature()->toDetailString());
    return id;
}

std::string FunctionIdGenerator::generateFor(std::shared_ptr<ASTFunctionInvocationExpressionNode> functionInvocationExpressionNode) {
    auto id = functionInvocationExpressionNode->getFunction()->getId() + "."
              + MD5().operator()(functionInvocationExpressionNode->getArguments()->getTypeSignature()->toDetailString());
    return id;
}

std::string FunctionIdGenerator::generateFor(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> objectAccessInvocationExpressionNode) {
    auto id = objectAccessInvocationExpressionNode->getName() + "."
              + MD5().operator()(objectAccessInvocationExpressionNode->getArguments()->getTypeSignature()->toDetailString());
    return id;
}

std::string FunctionIdGenerator::generateFor(std::string name, std::shared_ptr<InvocableTypeSignature> invocableTypeSignature) {
    auto id = name + "." + MD5().operator()(invocableTypeSignature->toDetailString());
    return id;
}

std::string FunctionIdGenerator::generateFor(std::string moduleId, std::string name, std::shared_ptr<InvocableTypeSignature> invocableTypeSignature) {
    auto id = FunctionIdGenerator::generateFor(name, invocableTypeSignature);
    if (moduleId.empty()) {
        return id;
    }
    return moduleId + "." + id;
}

std::string FunctionIdGenerator::generateFor(std::shared_ptr<InvocableTypeSignature> invocableTypeSignature) {
    return MD5().operator()(invocableTypeSignature->toDetailString());
}

std::string FunctionIdGenerator::generateFor(std::string functionName, std::string parameterDetailString) {
    auto id = functionName + "." + MD5().operator()(parameterDetailString);
    return id;
}