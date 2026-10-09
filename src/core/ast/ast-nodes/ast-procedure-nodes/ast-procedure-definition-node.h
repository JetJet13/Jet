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
// Created by Johny Georges on 2024-10-25.
//

#ifndef JETLANG_AST_PROCEDURE_DEFINITION_NODE_H
#define JETLANG_AST_PROCEDURE_DEFINITION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-name-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "ast-procedure-node.h"

class ASTProcedureDefinitionNode : public ASTNode {
private:
    std::shared_ptr<ASTProcedureNode> _procedureKeyword;
    std::shared_ptr<ASTFunctionNameNode> _name;
    std::shared_ptr<ASTFunctionParameterListNode> _parameters;
public:
    explicit ASTProcedureDefinitionNode(std::shared_ptr<ASTProcedureNode> functionKeyword, std::shared_ptr<ASTFunctionNameNode> name, std::shared_ptr<ASTFunctionParameterListNode> parameters);
    std::shared_ptr<ASTFunctionParameterListNode> getParameters();
    std::shared_ptr<ASTFunctionNameNode> getName();
    uint64_t numParameters();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_PROCEDURE_DEFINITION_NODE_H
