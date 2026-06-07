//
// Created by Johny Georges on 2026-06-06.
//

#include "ast-left-brace-base-node.h"
#include "../ast-enum-nodes/ast-enum-key-value-list-start-node.h"
#include "../ast-tuple-nodes/ast-tuple-list-start-node.h"
#include "../ast-control-flow-nodes/ast-control-flow-start-node.h"
#include "../ast-module-nodes/ast-module-list-start-node.h"
#include "../ast-import-nodes/ast-import-module-list-start-node.h"
#include "../ast-interface-nodes/ast-interface-start-node.h"
#include "../ast-type-nodes/ast-tuple-type-nodes/ast-tuple-type-start-node.h"
#include "../ast-block-nodes/ast-block-start-node.h"

ASTNode* ASTLeftBraceBaseNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_INTERMEDIATE_MODE) {
        return this;
    }

    if (mode == SA_TYPE_PARAMETER_LIST_MODE ||
        mode == SA_LAMBDA_TYPE_PARAMETER_LIST_MODE ||
        mode == SA_TUPLE_TYPE_MODE ||
        (prevNode && prevNode.value()->isOneOf({ AST_ARRAY_TYPE_START_NODE, AST_TYPE_COLON_NODE, AST_INTERFACE_COLON_NODE, AST_STRUCT_TYPE_COLON_NODE, AST_TYPE_ASSIGNMENT_OPERATOR_NODE }))
            ) {
        return new ASTTupleTypeStartNode(_lexeme);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_TYPE_NODE, AST_PROCEDURE_PARAMETER_LIST_NODE })) {
        return new ASTBlockStartNode(_lexeme);
    }

    if (!prevNode || mode == SA_FUNCTION_ARGUMENT_LIST_MODE || mode == SA_STRUCT_MODE || prevNode.value()->isOneOf({ AST_VARIABLE_INIT_NODE, AST_VARIABLE_ASSIGNMENT_NODE, AST_REF_VALUE_ASSIGNMENT_NODE,  AST_CLASS_PROPERTY_INIT_NODE, AST_STRUCT_COLON_NODE, AST_LEFT_BRACKET_NODE, AST_REF_NODE, AST_COMMA_NODE, AST_FUNCTION_RETURN_NODE, AST_GROUP_START_NODE, AST_ARRAY_ACCESS_ASSIGNMENT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE })) {
        return new ASTTupleListStartNode(_lexeme);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_ENUM_NAME_NODE })) {
        return new ASTEnumKeyValueListStartNode(_lexeme);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_INTERFACE_DEFINITION_NODE })) {
        return new ASTInterfaceStartNode(_lexeme);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_MODULE_NAME_NODE })) {
        return new ASTModuleListStartNode(_lexeme);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_MODULE_ACCESS_NODE })) {
        return new ASTImportModuleListStartNode(_lexeme);
    }

    if (mode == SA_CONTROL_FLOW_MODE) {
        return new ASTControlFlowStartNode(_lexeme);
    }

    return new ASTBlockStartNode(_lexeme);
}

ASTNodeType ASTLeftBraceBaseNode::getNodeType() {
    return AST_LEFT_BRACE_BASE_NODE;
}

std::string ASTLeftBraceBaseNode::toString() {
    return "LEFT_BRACE_BASE";
}