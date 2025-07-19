//
// Created by Johny Georges on 2024-01-10.
//

#ifndef JETLANG_SYNTAX_ANALYZER_H
#define JETLANG_SYNTAX_ANALYZER_H

#include <deque>
#include <stack>
#include "../../token/token-table.h"
#include "../../lexeme/lexeme.h"
#include "../../ast/ast.h"
#include "../../ast/ast-nodes/ast-file-node.h"
#include "../lexical-analyzer/lexical-analyzer.h"
#include "reducer/reducer.h"
#include "recognizer-result/recognizer-result.h"
#include "handle/handle.h"
#include "lexeme-transformer/lexeme-transformer.h"
#include "syntax-dfa/syntax-dfa.h"
#include "../../../shared/utils/logger/logger.h"
#include "lexeme-transformer/lexeme-transformer.h"
#include "../../ast/ast-nodes/ast-block-nodes/ast-block-node.h"
#include "types/syntax-analyzer-mode.h"
#include "recognizer/recognizer.h"
#include "ast-node-id-assignor/ast-node-id-assignor.h"
#include "scope/scope.h"
#include "file-scope/file-scope.h"
#include "syntax-analyzer-result/syntax-analyzer-result.h"

/* This SyntaxAnalyzer is a LALR(1) parser that performs bottom-up parsing
 * Instructions:
 * 1. consume each token from left to right one by one with the option to look-ahead 1 token
 * 2. Push each token onto the handle stack
 * 2. create a handle composed of one or more tokens living on the stack
 * 3. check to see if the handle can be 'reduced' into an AST Node
 * 4. if it can, create the AST Node and append it to the state stack
 */

class SyntaxAnalyzer {
private:
    TokenTable* _tokenTable;
    Recognizer* _recognizer;
    ASTNodeIdAssignor* _astNodeIdAssignor;
    Reducer _reducer;
    LexicalAnalyzer* _lexicalAnalyzer;
    Handle _handle;
    LexemeTransformer _lexemeTransformer;
    std::stack<SyntaxAnalyzerMode> _modeStack;
    std::stack<Scope> _scopeStack;
    std::stack<std::stack<ASTNode*>*> _recognizeStack;
    std::vector<std::string> _syntaxErrorList;
    bool _shiftDisabled;
    RecognizerResult* recognizeHandle();
    void shift();
    void reduceHandle(RecognizerResult* recognizerResult, FileScope* fileScope);
    void popFromStack();
    void prepHandleForRecognizer();
    void updateModeIfNecessary(ASTNodeType astNodeType);
    void handleSyntaxErrors();
public:
    SyntaxAnalyzer(TokenTable* tokenTable, LexicalAnalyzer* lexicalAnalyzer);
    SyntaxAnalyzerResult* analyze(std::string &filePath);
};

#endif //JETLANG_SYNTAX_ANALYZER_H


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
 *  stack = [<var-init> <int-exp>] _handle = [ ; ] // reduce
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
 *  stack = [<var-init>] _handle = [] // reduce
 *  stack = [<var-init>] _handle = [<int>] // shift
 *  stack = [<var-init>] _handle = [<int> <binary-op>] // shift
 *  stack = [<var-init>] _handle = [<int> <binary-op> <int>] // reduce
 *  stack = [<binary-exp> <var-init>] _handle = [ ; ] // shift
 *  stack = [<var-init>] _handle = [<binary-exp> ; ] // recycle
 *  stack = [] _handle = [ <var-init> <binary-exp> ; ] // recycle
 *  stack = [<var-dec>] _handle = [ ; ] // reduce
 *  stack = [] _handle = [] // done
 *
 *
 *
 *  let foo = 10 + 2 + 3;
 *  ---------------------------------
 *  stack = [] _handle = []
 *  stack = [] _handle = [<var-type>] // shift
 *  stack = [] _handle = [<var-type> <id>] // shift
 *  stack = [] _handle = [<var-type> <id> <assign-op>] // shift
 *  stack = [<var-init>] _handle = [] // reduce
 *  stack = [<var-init>] _handle = [<int>] // shift
 *  stack = [<var-init>] _handle = [<int> <binary-op>] // shift
 *  stack = [<var-init>] _handle = [<int> <binary-op> <int>] // reduce
 *  stack = [<binary-exp> <var-init>] _handle = [ <binary-op> ] // shift
 *  stack = [<binary-exp> <var-init>] _handle = [ <binary-op> <int> ] // shift
 *  stack = [<binary-exp> <var-init>] _handle = [ <binary-op> <int> ; ] // shift
 *  stack = [<var-init>] _handle = [<binary-exp> <binary-op> <int> ; ] // recycle
 *  stack = [<var-dec> <binary-exp>] _handle = [ ; ] // reduce
 *  stack = [<var-dec> <binary-exp>] _handle = [ ; ] // recycle
 *  stack = [] _handle = [ <var-dec> <binary-exp> ; ] // reduce
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
