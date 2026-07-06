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
class ClassInstanceIRInjectorStrategy;
class ClassPropertyAssignmentIRInjectorStrategy;
class ClassPropertyRefValueAssignmentIRInjectorStrategy;
class RefValueAssignmentIRInjectorStrategy;
class VariableAssignmentIRInjectorStrategy;
class ArrayAccessAssignmentIRInjectorStrategy;
class ArrayAccessRefAssignmentIRInjectorStrategy;
class ObjectAccessAssignmentIRInjectorStrategy;
class ObjectAccessRefAssignmentIRInjectorStrategy;
class TupleAccessAssignmentIRInjectorStrategy;
class TupleAccessRefAssignmentIRInjectorStrategy;
class ModuleAccessAssignmentIRInjectorStrategy;
class ModuleAccessRefAssignmentIRInjectorStrategy;
class ClassStaticPropertyAssignmentIRInjectorStrategy;
class ClassStaticPropertyRefAssignmentIRInjectorStrategy;
class IfStatementIRInjectorStrategy;
class WhileStatementIRInjectorStrategy;
class ForInStatementIRInjectorStrategy;
class ExpressionStatementIRInjectorStrategy;
class ProcedureDeclarationIRInjectorStrategy;
class FunctionDeclarationIRInjectorStrategy;
class TypeValueIRInjectorStrategy;
class BlockIRInjectorStrategy;
class ClassIRInjectorStrategy;

class IRInjector {
private:
    std::unordered_map<TypeSource, std::shared_ptr<IRInjectorStrategy>, std::hash<int>> _injectorMap;
    std::shared_ptr<StringIRInjectorStrategy> _stringIRInjector;
    std::shared_ptr<LiteralIRInjectorStrategy> _literalIRInjector;
    std::shared_ptr<ArrayIRInjectorStrategy> _arrayIRInjector;
    std::shared_ptr<StructIRInjectorStrategy> _structIRInjector;
    std::shared_ptr<TupleIRInjectorStrategy> _tupleIRInjector;
    std::shared_ptr<PointerIRInjectorStrategy> _pointerIRInjector;
    std::shared_ptr<VoidIRInjectorStrategy> _voidIRInjector;
    std::shared_ptr<RefIRInjectorStrategy> _refIRInjector;
    std::shared_ptr<LambdaIRInjectorStrategy> _lambdaIRInjector;
    std::shared_ptr<EnumIRInjectorStrategy> _enumIRInjector;
    std::shared_ptr<NewClassInstanceIRInjectorStrategy> _newClassInstanceIRInjectorStrategy;
    std::shared_ptr<ClassInstanceIRInjectorStrategy> _classInstanceIRInjectorStrategy;
    VariableIRInjectorStrategy* _variableIRInjector;
    ModuleIRInjectorStrategy* _moduleIRInjector;
    FunctionParameterIRInjectorStrategy* _functionParameterIRInjector;
    FunctionReturnIRInjectorStrategy* _functionReturnIRInjector;
    ClassPropertyAssignmentIRInjectorStrategy* _classPropertyAssignmentIRInjectorStrategy;
    ClassPropertyRefValueAssignmentIRInjectorStrategy* _classPropertyRefValueAssignmentIRInjectorStrategy;
    RefValueAssignmentIRInjectorStrategy* _refValueAssignmentIRInjectorStrategy;
    VariableAssignmentIRInjectorStrategy* _variableAssignmentIRInjectorStrategy;
    ArrayAccessAssignmentIRInjectorStrategy* _arrayAccessAssignmentIRInjectorStrategy;
    ArrayAccessRefAssignmentIRInjectorStrategy* _arrayAccessRefAssignmentIRInjectorStrategy;
    ObjectAccessAssignmentIRInjectorStrategy* _objectAccessAssignmentIRInjectorStrategy;
    ObjectAccessRefAssignmentIRInjectorStrategy* _objectAccessRefAssignmentIRInjectorStrategy;
    TupleAccessAssignmentIRInjectorStrategy* _tupleAccessAssignmentIRInjectorStrategy;
    TupleAccessRefAssignmentIRInjectorStrategy* _tupleAccessRefAssignmentIRInjectorStrategy;
    ModuleAccessAssignmentIRInjectorStrategy* _moduleAccessAssignmentIRInjectorStrategy;
    ModuleAccessRefAssignmentIRInjectorStrategy* _moduleAccessRefAssignmentIRInjectorStrategy;
    ClassStaticPropertyAssignmentIRInjectorStrategy* _classStaticPropertyAssignmentIRInjectorStrategy;
    ClassStaticPropertyRefAssignmentIRInjectorStrategy* _classStaticPropertyRefAssignmentIRInjectorStrategy;
    IfStatementIRInjectorStrategy* _ifStatementIRInjectorStrategy;
    WhileStatementIRInjectorStrategy* _whileStatementIRInjectorStrategy;
    ForInStatementIRInjectorStrategy* _forInStatementIRInjectorStrategy;
    ExpressionStatementIRInjectorStrategy* _expressionStatementIRInjectorStrategy;
    ProcedureDeclarationIRInjectorStrategy* _procedureDeclarationIRInjectorStrategy;
    FunctionDeclarationIRInjectorStrategy* _functionDeclarationIRInjectorStrategy;
    TypeValueIRInjectorStrategy* _typeValueIRInjectorStrategy;
    BlockIRInjectorStrategy* _blockIRInjectorStrategy;
    ClassIRInjectorStrategy* _classIRInjectorStrategy;
    void init();
    std::pair<TypeSource, IRInjectorStrategy*> insert(TypeSource typeSignature, IRInjectorStrategy* injector);
public:
    IRInjector();
    void inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRNode> irNode, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
    void inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRDeclarationNode> irDeclaration, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
    void inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRStatementNode> irStatement, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
    void inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRBlockNode> irNode, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRType> irType, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRExpressionNode> irExpression, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
    void injectVoidReturnType(std::shared_ptr<IRBlockNode> irBlock);
    llvm::Value* injectStringGlobalVariable(std::shared_ptr<IRBlockNode> irBlock, std::string id, std::string rawString, std::shared_ptr<IRModuleNode> irModule);
    llvm::AllocaInst* injectRawString(std::shared_ptr<IRBlockNode> irBlock, std::string rawString);
};

#endif //JETLANG_IR_INJECTOR_H
