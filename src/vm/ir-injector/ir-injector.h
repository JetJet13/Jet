//
// Created by Johny Georges on 2024-08-15.
//

#ifndef JETLANG_IR_INJECTOR_H
#define JETLANG_IR_INJECTOR_H

#include "../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../ir-nodes/ir-block-node.h"
#include "../ir-lookup-table/ir-lookup-table.h"
#include "../ir-nodes/ir-module-node.h"
#include "../ir-nodes/ir-declaration-nodes/ir-declaration-node.h"
#include "../ir-nodes/ir-statement-nodes/ir-statement-node.h"
#include "../types/ir-operation-type.h"

class IRInjectorStrategy;
class StringIRInjectorStrategy;
class LiteralIRInjectorStrategy;
class ArrayIRInjectorStrategy;
class StructIRInjectorStrategy;
class TupleIRInjectorStrategy;
class VariableIRInjectorStrategy;
class ModuleIRInjectorStrategy;
class LambdaIRInjectorStrategy;
class EnumIRInjectorStrategy;
class FunctionParameterIRInjectorStrategy;
class FunctionReturnIRInjectorStrategy;
class NewClassInstanceIRInjectorStrategy;
class ClassPropertyAssignmentIRInjectorStrategy;
class VariableAssignmentIRInjectorStrategy;
class ArrayAccessAssignmentIRInjectorStrategy;
class IfStatementIRInjectorStrategy;
class ProcedureDeclarationIRInjectorStrategy;
class FunctionDeclarationIRInjectorStrategy;

class IRInjector {
private:
    std::unordered_map<TypeSource, IRInjectorStrategy*, std::hash<int>> _injectorMap;
    StringIRInjectorStrategy* _stringIRInjector;
    LiteralIRInjectorStrategy* _literalIRInjector;
    ArrayIRInjectorStrategy* _arrayIRInjector;
    StructIRInjectorStrategy* _structIRInjector;
    TupleIRInjectorStrategy* _tupleIRInjector;
    VariableIRInjectorStrategy* _variableIRInjector;
    ModuleIRInjectorStrategy* _moduleIRInjector;
    LambdaIRInjectorStrategy* _lambdaIRInjector;
    EnumIRInjectorStrategy* _enumIRInjectorStrategy;
    FunctionParameterIRInjectorStrategy* _functionParameterIRInjector;
    FunctionReturnIRInjectorStrategy* _functionReturnIRInjector;
    NewClassInstanceIRInjectorStrategy* _newClassInstanceIRInjectorStrategy;
    ClassPropertyAssignmentIRInjectorStrategy* _classPropertyAssignmentIRInjectorStrategy;
    VariableAssignmentIRInjectorStrategy* _variableAssignmentIRInjectorStrategy;
    ArrayAccessAssignmentIRInjectorStrategy* _arrayAccessAssignmentIRInjectorStrategy;
    IfStatementIRInjectorStrategy* _ifStatementIRInjectorStrategy;
    ProcedureDeclarationIRInjectorStrategy* _procedureDeclarationIRInjectorStrategy;
    FunctionDeclarationIRInjectorStrategy* _functionDeclarationIRInjectorStrategy;
    void init();
    std::pair<TypeSource, IRInjectorStrategy*> insert(TypeSource typeSignature, IRInjectorStrategy* injector);
public:
    IRInjector();
    void inject(IRBlockNode* irBlock, IRNode* irNode, IRModuleNode* irModule, IRLookupTable* scope);
    void inject(IRBlockNode* irBlock, IRDeclarationNode* irDeclaration, IRModuleNode* irModule, IRLookupTable* scope);
    void inject(IRBlockNode* irBlock, IRStatementNode* irStatement, IRModuleNode* irModule, IRLookupTable* scope);
    llvm::Value* inject(IRBlockNode* irBlock, IRExpressionNode* irExpression, IROperationType irOperationType, IRModuleNode* irModule, IRLookupTable* scope);
    void injectVoidReturnType(IRBlockNode* irBlock);
};

#endif //JETLANG_IR_INJECTOR_H
