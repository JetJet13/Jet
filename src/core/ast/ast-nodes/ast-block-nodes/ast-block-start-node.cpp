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
// Created by Johny Georges on 2024-03-13.
//

#include "ast-block-start-node.h"
#include "../ast-struct-nodes/ast-struct-start-node.h"
#include "../ast-enum-nodes/ast-enum-key-value-list-start-node.h"
#include "../ast-tuple-nodes/ast-tuple-list-start-node.h"
#include "../ast-control-flow-nodes/ast-control-flow-start-node.h"
#include "../ast-module-nodes/ast-module-list-start-node.h"
#include "../ast-import-nodes/ast-import-module-list-start-node.h"
#include "../ast-interface-nodes/ast-interface-start-node.h"
#include "../ast-type-nodes/ast-struct-type-nodes/ast-struct-type-start-node.h"
#include "../ast-type-nodes/ast-tuple-type-nodes/ast-tuple-type-start-node.h"

std::shared_ptr<ASTNode> ASTBlockStartNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_TYPE_PARAMETER_LIST_MODE ||
        mode == SA_LAMBDA_TYPE_PARAMETER_LIST_MODE ||
        mode == SA_TUPLE_TYPE_MODE ||
        (prevNode && prevNode.value()->isOneOf({AST_LAMBDA_ARROW_NODE, AST_ARRAY_TYPE_START_NODE, AST_TYPE_COLON_NODE, AST_INTERFACE_COLON_NODE, AST_STRUCT_TYPE_COLON_NODE, AST_TYPE_ASSIGNMENT_OPERATOR_NODE }))
            ) {
        return std::make_shared<ASTTupleTypeStartNode>(_lexeme);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_TYPE_NODE, AST_FUNCTION_PARAMETER_LIST_NODE })) {
        return shared_from_this();
    }

    if (!prevNode || mode == SA_FUNCTION_ARGUMENT_LIST_MODE || mode == SA_STRUCT_MODE || prevNode.value()->isOneOf({AST_LAMBDA_FAT_ARROW_NODE, AST_VARIABLE_INIT_NODE, AST_VARIABLE_ASSIGNMENT_NODE, AST_SHARED_VALUE_ASSIGNMENT_NODE, AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE, AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE, AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE, AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE, AST_CLASS_PROPERTY_INIT_NODE, AST_STRUCT_COLON_NODE, AST_LEFT_BRACKET_NODE, AST_SHARE_NODE, AST_COMMA_NODE, AST_FUNCTION_RETURN_NODE, AST_GROUP_START_NODE, AST_ARRAY_ACCESS_ASSIGNMENT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE })) {
        return std::make_shared<ASTTupleListStartNode>(_lexeme);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_ENUM_NAME_NODE })) {
        return std::make_shared<ASTEnumKeyValueListStartNode>(_lexeme);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_INTERFACE_DEFINITION_NODE })) {
        return std::make_shared<ASTInterfaceStartNode>(_lexeme);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_MODULE_NAME_NODE })) {
        return std::make_shared<ASTModuleListStartNode>(_lexeme);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_MODULE_ACCESS_NODE })) {
        return std::make_shared<ASTImportModuleListStartNode>(_lexeme);
    }

    if (mode == SA_CONTROL_FLOW_MODE) {
        return std::make_shared<ASTControlFlowStartNode>(_lexeme);
    }

    return shared_from_this();
}

ASTNodeType ASTBlockStartNode::getNodeType() {
    return AST_BLOCK_START_NODE;
}

std::string ASTBlockStartNode::toString() {
    return "BLOCK_START";
}