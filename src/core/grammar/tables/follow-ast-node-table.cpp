//
// Created by Johny Georges on 2024-02-10.
//

#include "follow-ast-node-table.h"

FollowASTNodeTable::FollowASTNodeTable() {
    _followAstNodeMap = std::unordered_map<ASTNodeType, std::vector<ASTNodeType>*, std::hash<int>>();
    this->init();
}

bool FollowASTNodeTable::isValidFollowASTNode(ASTNodeType followASTNodeType, ASTNodeType astNodeType) {
    auto viableFollowAstNodeTypes = _followAstNodeMap.find(astNodeType);
    if (viableFollowAstNodeTypes == _followAstNodeMap.end()) {
        return false;
    }
    return std::find(viableFollowAstNodeTypes->second->begin(),
                     viableFollowAstNodeTypes->second->end(),
                     followASTNodeType) != viableFollowAstNodeTypes->second->end();
}

void FollowASTNodeTable::init() {
    this->add(AST_VARIABLE_TYPE_NODE, new std::vector<ASTNodeType> {
            AST_IDENTIFIER_NODE
    });

    this->add(AST_IDENTIFIER_NODE, new std::vector<ASTNodeType> {
            AST_ASSIGNMENT_OPERATOR_NODE,
            AST_BINARY_ARITHMETIC_OPERATOR_NODE,
            AST_LOGICAL_OPERATOR_NODE,
            AST_SYMBOL_NODE,
            AST_TERMINATOR_NODE
    });

    this->add(AST_ASSIGNMENT_OPERATOR_NODE, new std::vector<ASTNodeType> {
           AST_EXPRESSION_NODE,
           AST_BOOLEAN_LITERAL_NODE,
           AST_INT_LITERAL_NODE,
           AST_FLOAT_LITERAL_NODE,
           AST_STRING_LITERAL_NODE,
           AST_CHAR_LITERAL_NODE
    });
    this->add(AST_BINARY_ARITHMETIC_OPERATOR_NODE, new std::vector<ASTNodeType> {
            AST_EXPRESSION_NODE,
            AST_BOOLEAN_LITERAL_NODE,
            AST_INT_LITERAL_NODE,
            AST_FLOAT_LITERAL_NODE,
            AST_STRING_LITERAL_NODE,
            AST_CHAR_LITERAL_NODE
    });
    this->add(AST_LOGICAL_OPERATOR_NODE, new std::vector<ASTNodeType> {
            AST_EXPRESSION_NODE,
            AST_BOOLEAN_LITERAL_NODE,
            AST_INT_LITERAL_NODE,
            AST_FLOAT_LITERAL_NODE,
            AST_STRING_LITERAL_NODE,
            AST_CHAR_LITERAL_NODE
    });
    this->add(AST_EXPRESSION_NODE, new std::vector<ASTNodeType> {
           AST_SYMBOL_NODE,
           AST_TERMINATOR_NODE
    });
    this->add(AST_BOOLEAN_LITERAL_NODE, new std::vector<ASTNodeType> {
            AST_BINARY_ARITHMETIC_OPERATOR_NODE,
            AST_LOGICAL_OPERATOR_NODE,
            AST_SYMBOL_NODE,
            AST_TERMINATOR_NODE
    });
    this->add(AST_INT_LITERAL_NODE, new std::vector<ASTNodeType> {
            AST_BINARY_ARITHMETIC_OPERATOR_NODE,
            AST_LOGICAL_OPERATOR_NODE,
            AST_SYMBOL_NODE,
            AST_TERMINATOR_NODE
    });

    this->add(AST_FLOAT_LITERAL_NODE, new std::vector<ASTNodeType> {
            AST_BINARY_ARITHMETIC_OPERATOR_NODE,
            AST_LOGICAL_OPERATOR_NODE,
            AST_SYMBOL_NODE,
            AST_TERMINATOR_NODE
    });

    this->add(AST_STRING_LITERAL_NODE, new std::vector<ASTNodeType> {
            AST_BINARY_ARITHMETIC_OPERATOR_NODE,
            AST_LOGICAL_OPERATOR_NODE,
            AST_SYMBOL_NODE,
            AST_TERMINATOR_NODE
    });

    this->add(AST_CHAR_LITERAL_NODE, new std::vector<ASTNodeType> {
            AST_BINARY_ARITHMETIC_OPERATOR_NODE,
            AST_LOGICAL_OPERATOR_NODE,
            AST_SYMBOL_NODE,
            AST_TERMINATOR_NODE
    });


    this->add(AST_SYMBOL_NODE, new std::vector<ASTNodeType> {
            AST_IDENTIFIER_NODE,
            AST_EXPRESSION_NODE,
            AST_BOOLEAN_LITERAL_NODE,
            AST_INT_LITERAL_NODE,
            AST_FLOAT_LITERAL_NODE,
            AST_STRING_LITERAL_NODE,
            AST_CHAR_LITERAL_NODE,
            AST_TERMINATOR_NODE
    });

    this->add(AST_BANG_OPERATOR_NODE, new std::vector<ASTNodeType> {
            AST_IDENTIFIER_NODE,
            AST_EXPRESSION_NODE,
            AST_BOOLEAN_LITERAL_NODE,
            AST_INT_LITERAL_NODE,
            AST_FLOAT_LITERAL_NODE,
            AST_STRING_LITERAL_NODE,
            AST_CHAR_LITERAL_NODE,
    });
}

void FollowASTNodeTable::add(ASTNodeType astNodeType, std::vector<ASTNodeType>* followAstNodeTypes) {
    _followAstNodeMap.insert(std::pair<ASTNodeType, std::vector<ASTNodeType>*>(astNodeType, followAstNodeTypes));
}