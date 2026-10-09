// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2025-08-02.
//

#ifndef JETLANG_FUNCTION_ID_GENERATOR_H
#define JETLANG_FUNCTION_ID_GENERATOR_H

#include <string>
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-function-invocation-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-class-method-declaration-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-invocation-expression-node.h"

class FunctionIdGenerator {
public:
    static std::string getNameFromId(std::string functionId);
    static std::string generateFor(std::shared_ptr<ASTClassMethodDeclarationNode> classMethodDeclarationNode);
    static std::string generateFor(std::shared_ptr<ASTFunctionDeclarationNode> functionDeclarationNode);
    static std::string generateFor(std::shared_ptr<ASTProcedureDeclarationNode> procedureDeclarationNode);
    static std::string generateFor(std::shared_ptr<ASTFunctionInvocationExpressionNode> functionInvocationExpressionNode);
    static std::string generateFor(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> objectAccessInvocationExpressionNode);
    static std::string generateFor(std::string name, std::shared_ptr<InvocableTypeSignature> invocableTypeSignature);
    static std::string generateFor(std::string moduleId, std::string name, std::shared_ptr<InvocableTypeSignature> invocableTypeSignature);
    static std::string generateFor(std::shared_ptr<InvocableTypeSignature> invocableTypeSignature);
    static std::string generateFor(std::string functionName, std::string parameterDetailString = "");
};

#endif //JETLANG_FUNCTION_ID_GENERATOR_H
