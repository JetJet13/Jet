//
// Created by Johny Georges on 2024-08-15.
//

#ifndef JETLANG_IR_INJECTOR_H
#define JETLANG_IR_INJECTOR_H

#include "../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../ir-lookup-table/ir-lookup-table.h"
#include "../ir-nodes/ir-module-node.h"
#include "../ir-nodes/ir-declaration-nodes/ir-declaration-node.h"
#include "../ir-nodes/ir-statement-nodes/ir-statement-node.h"
#include "../types/ir-operation-type.h"
#include "../ir-nodes/ir-type-declaration-nodes/ir-type-declaration-node.h"
#include "../ir-operation/ir-operation.h"

class IRInjectorStrategy;
class StringIRInjectorStrategy;
class LiteralIRInjectorStrategy;
class ArrayIRInjectorStrategy;
class StructIRInjectorStrategy;
class TupleIRInjectorStrategy;
class PointerIRInjectorStrategy;
class VoidIRInjectorStrategy;
class RefIRInjectorStrategy;
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
class ObjectAccessAssignmentIRInjectorStrategy;
class TupleAccessAssignmentIRInjectorStrategy;
class IfStatementIRInjectorStrategy;
class WhileStatementIRInjectorStrategy;
class ForInStatementIRInjectorStrategy;
class ExpressionStatementIRInjectorStrategy;
class PrintStatementIRInjectorStrategy;
class ProcedureDeclarationIRInjectorStrategy;
class FunctionDeclarationIRInjectorStrategy;
class TypeValueIRInjectorStrategy;
class BlockIRInjectorStrategy;

class IRInjector {
private:
    std::unordered_map<TypeSource, IRInjectorStrategy*, std::hash<int>> _injectorMap;
    StringIRInjectorStrategy* _stringIRInjector;
    LiteralIRInjectorStrategy* _literalIRInjector;
    ArrayIRInjectorStrategy* _arrayIRInjector;
    StructIRInjectorStrategy* _structIRInjector;
    TupleIRInjectorStrategy* _tupleIRInjector;
    PointerIRInjectorStrategy* _pointerIRInjector;
    VoidIRInjectorStrategy* _voidIRInjector;
    RefIRInjectorStrategy* _refIRInjector;
    VariableIRInjectorStrategy* _variableIRInjector;
    ModuleIRInjectorStrategy* _moduleIRInjector;
    LambdaIRInjectorStrategy* _lambdaIRInjector;
    EnumIRInjectorStrategy* _enumIRInjector;
    FunctionParameterIRInjectorStrategy* _functionParameterIRInjector;
    FunctionReturnIRInjectorStrategy* _functionReturnIRInjector;
    NewClassInstanceIRInjectorStrategy* _newClassInstanceIRInjectorStrategy;
    ClassPropertyAssignmentIRInjectorStrategy* _classPropertyAssignmentIRInjectorStrategy;
    VariableAssignmentIRInjectorStrategy* _variableAssignmentIRInjectorStrategy;
    ArrayAccessAssignmentIRInjectorStrategy* _arrayAccessAssignmentIRInjectorStrategy;
    ObjectAccessAssignmentIRInjectorStrategy* _objectAccessAssignmentIRInjectorStrategy;
    TupleAccessAssignmentIRInjectorStrategy* _tupleAccessAssignmentIRInjectorStrategy;
    IfStatementIRInjectorStrategy* _ifStatementIRInjectorStrategy;
    WhileStatementIRInjectorStrategy* _whileStatementIRInjectorStrategy;
    ForInStatementIRInjectorStrategy* _forInStatementIRInjectorStrategy;
    ExpressionStatementIRInjectorStrategy* _expressionStatementIRInjectorStrategy;
    PrintStatementIRInjectorStrategy* _printStatementIRInjectorStrategy;
    ProcedureDeclarationIRInjectorStrategy* _procedureDeclarationIRInjectorStrategy;
    FunctionDeclarationIRInjectorStrategy* _functionDeclarationIRInjectorStrategy;
    TypeValueIRInjectorStrategy* _typeValueIRInjectorStrategy;
    BlockIRInjectorStrategy* _blockIRInjectorStrategy;
    void init();
    std::pair<TypeSource, IRInjectorStrategy*> insert(TypeSource typeSignature, IRInjectorStrategy* injector);
public:
    IRInjector();
    void inject(IRBlockNode* irBlock, IRNode* irNode, IRModuleNode* irModule, IRLookupTable* scope);
    void inject(IRBlockNode* irBlock, IRDeclarationNode* irDeclaration, IRModuleNode* irModule, IRLookupTable* scope);
    void inject(IRBlockNode* irBlock, IRStatementNode* irStatement, IRModuleNode* irModule, IRLookupTable* scope);
    void inject(IRBlockNode* irBlock, IRBlockNode* irNode, IRModuleNode* irModule, IRLookupTable* scope);
    llvm::Value* inject(IRBlockNode* irBlock, IRType* irType);
    llvm::Value* inject(IRBlockNode* irBlock, IRExpressionNode* irExpression, IROperation* irOperation, IRModuleNode* irModule, IRLookupTable* scope);
    void injectVoidReturnType(IRBlockNode* irBlock);
};

#endif //JETLANG_IR_INJECTOR_H
