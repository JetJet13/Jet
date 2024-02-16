//
// Created by Johny Georges on 2024-02-08.
//

#include "recognizer.h"
#include "../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-type-node.h"
#include "../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-init-node.h"
#include "../../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"


Recognizer::Recognizer(Handle* handle) {
    _handle = handle;
}

std::optional<ReduceNode*> Recognizer::recognizeVariableTypeNode() {
    int variableInitNodeSize = 3;
    if (_handle->size() != variableInitNodeSize) {
        return {};
    }

    auto firstNodeOk = _handle->at(0).value()->getNodeType() == AST_VARIABLE_TYPE_NODE;
    auto secondNodeOk = _handle->at(1).value()->getNodeType() == AST_IDENTIFIER_NODE;
    auto thirdNodeOk = _handle->at(2).value()->getNodeType() == AST_ASSIGNMENT_OPERATOR_NODE;

    if (firstNodeOk && secondNodeOk && thirdNodeOk) {
        return new ReduceNode(
                new ASTVariableInitNode((ASTVariableTypeNode*)_handle->at(0).value(),
                                        (ASTIdentifierNode*)_handle->at(1).value()
                                        ),
                variableInitNodeSize);
    }
    return {};
}

std::optional<ReduceNode*> Recognizer::recognizeIntLiteralNode() {
    if (_handle->size() == 1) {
        return {};
    } else if (_handle->size() == 2) {
        return this->isLiteralAssignment();
    } else if (_handle->size() == 3 && ASTNodeUtils::isBinaryOperatorNode(_handle->at(1).value())) {

    }


}

std::optional<ReduceNode*> Recognizer::isLiteralAssignment() {
    if (_handle->size() != 2) {
        return {};
    }


    if (ASTNodeUtils::isLiteralNode(_handle->at(0).value()) &&
    ASTNodeUtils::isTerminatorNode(_handle->at(1).value())) {
        return new ReduceNode(_handle->at(0).value(), 1);
    }
    return {};
}

std::optional<ReduceNode*> Recognizer::recognize() {
    if (_handle->isEmpty()) {
        return {};
    }
    auto firstNode = _handle->at(0);
    switch (firstNode.value()->getNodeType()) {
        case AST_VARIABLE_TYPE_NODE:
           return this->recognizeVariableTypeNode();
        case AST_INT_LITERAL_NODE:

        default:
            return {};
    }
}


/*
 *  const mim = true;
 *  const moo = 'c';
 *  const bar = "hello";
 *  let foo = 10;
 *  ---------------------------------
 *  stack = [] _handle = []
 *  stack = [] _handle = [<var-type>] // shift
 *  stack = [] _handle = [<var-type> <id>] // shift
 *  stack = [] _handle = [<var-type> <id> <assign-op>] // shift
 *  stack = [<var-init>] _handle = [] // reduce
 *  stack = [<var-init>] _handle = [<int>] // shift
 *  stack = [<var-init>] _handle = [<int> ;] // shift
 *  stack = [<int> <var-init>] _handle = [ ; ] // reduce
 *  stack = [] _handle = [<int> <var-init> ; ] // recycle
 *  stack = [<int>] _handle = [<var-init> ; ] // reduce
 *  stack = [<var-init> <int>] _handle = [ ; ] // reduce
 *  stack = [] _handle = [<var-init> <int> ; ] // recycle
 *  stack = [<var-dec>] _handle = [ ; ] // reduce
 *  stack = [] _handle = [] // done
 *
 *
 *  let foo = 10 + 2;
 *  ---------------------------------
 *  stack = [] _handle = []
 *  stack = [] _handle = [<var-type>] // shift
 *  stack = [] _handle = [<var-type> <id>] // shift
 *  stack = [] _handle = [<var-type> <id> <assign-op>] // shift
 *  stack = [<var-init>] _handle = [<int>] // reduce
 *  stack = [<var-init>] _handle = [<int> <binary-op>] // shift
 *  stack = [<var-init>] _handle = [<int> <binary-op> <int>] // shift
 *  stack = [<var-init>] _handle = [<int> <binary-op> <int> ;] // shift
 *  stack = [<binary-exp> <var-init>] _handle = [ ; ] // reduce
 *  stack = [] _handle = [<binary-exp> <var-init> ; ] // recycle
 *  stack = [<binary-exp>] _handle = [<var-init> ; ] // reduce
 *  stack = [<var-init> <binary-exp>] _handle = [ ; ] // reduce
 *  stack = [] _handle = [<var-init> <binary-exp> ; ] // recycle
 *  stack = [<var-dec>] _handle = [ ; ] // reduce
 *  stack = [] _handle = [] // done
 *
 *
 *
 *
 *
 *
 * let zio = ((((foo && bar)))) && (moo && mim);
 * ---------------------------------
 * stack = [] _handle = []
 * stack = [] _handle = [<var-type>]
 * stack = [] _handle = [<var-type> <id>]
 * stack = [] _handle = [<var-type> <id> <assign-op>]
 * stack = [<var-init>] _handle = [ ( ]
 * stack = [<logical-exp> <var-init>] _handle = [ ( ]
 * stack = [<group-start> <group-start> <var-init>] _handle = [ ( ]
 * stack = [<group-start> <group-start> <group-start> <var-init>] _handle = [ ( ]
 * stack = [<group-start> <group-start> <group-start> <group-start> <var-init>] _handle = [ <id> ]
 * stack = [<group-start> <group-start> <group-start> <group-start> <var-init>] _handle = [ <id> && ]
 * stack = [<group-start> <group-start> <group-start> <group-start> <var-init>] _handle = [ <id> && <id> ]
 * stack = [<logical-exp> <group-start> <group-start> <group-start> <group-start> <var-init>] _handle = [ ) ]
 * stack = [<group-end> <logical-exp> <group-start> <group-start> <group-start> <group-start> <var-init>] _handle = [ ) ]
 * stack = [<group-end> <group-end> <logical-exp> <group-start> <group-start> <group-start> <group-start> <var-init>] _handle = [ ) ]
 * stack = [<group-end> <group-end> <group-end> <logical-exp> <group-start> <group-start> <group-start> <group-start> <var-init>] _handle = [ ) ]
 * stack = [<group-end> <group-end> <group-end> <group-end> <logical-exp> <group-start> <group-start> <group-start> <group-start> <var-init>] _handle = [ && ]
 * stack = [<logical-op> <group-end> <group-end> <group-end> <group-end> <logical-exp> <group-start> <group-start> <group-start> <group-start> <var-init>] _handle = [ ( ]
 * stack = [<group-start> <logical-op> <group-end> <group-end> <group-end> <group-end> <logical-exp> <group-start> <group-start> <group-start> <group-start> <var-init>] _handle = [ <id> && <id> ]
 * stack = [<logical-exp> <group-start> <logical-op> <group-end> <group-end> <group-end> <group-end> <logical-exp> <group-start> <group-start> <group-start> <group-start> <var-init>] _handle = [ ) ]
 * stack = [<group-end> <logical-exp> <group-start> <logical-op> <group-end> <group-end> <group-end> <group-end> <logical-exp> <group-start> <group-start> <group-start> <group-start> <var-init>] _handle = [ ; ]
 * stack = [] _handle = [<group-end> <logical-exp> <group-start> <logical-op> <group-end> <group-end> <group-end> <group-end> <logical-exp> <group-start> <group-start> <group-start> <group-start> <var-init> ; ]
 * stack = [<group-exp>] _handle = [<logical-op> <group-end> <group-end> <group-end> <group-end> <logical-exp> <group-start> <group-start> <group-start> <group-start> <var-init> ; ]
 * stack = [<logical-op> <group-exp>] _handle = [<group-end> <group-end> <group-end> <group-end> <logical-exp> <group-start> <group-start> <group-start> <group-start> <var-init> ; ]
 * stack = [<group-exp> <logical-op> <group-exp>] _handle = [ <var-init> ; ]
 * stack = [<var-init> <group-exp> <logical-op> <group-exp>] _handle = [ ; ]
 * stack = [] _handle = [<var-init> <group-exp> <logical-op> <group-exp> ; ]
 * stack = [<var-init>] _handle = [<group-exp> <logical-op> <group-exp> ; ]
 * stack = [<logical-exp> <var-init>] _handle = [ ; ]
 * stack = [] _handle = [<logical-exp> <var-init> ; ]
 * stack = [<logical-exp>] _handle = [<var-init> ; ]
 * stack = [<var-init> <logical-exp>] _handle = [ ; ]
 * stack = [] _handle = [<var-init> <logical-exp> ; ]
 * stack = [<var-dec>] _handle = [ ; ]
 * stack = [] _handle = []
 *
 *
 * */