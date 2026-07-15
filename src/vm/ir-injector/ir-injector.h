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
class SharedPtrIRInjectorStrategy;
class VariableIRInjectorStrategy;
class ModuleIRInjectorStrategy;
class LambdaIRInjectorStrategy;
class EnumIRInjectorStrategy;
class FunctionParameterIRInjectorStrategy;
class FunctionReturnIRInjectorStrategy;
class NewClassInstanceIRInjectorStrategy;
class ClassInstanceIRInjectorStrategy;
class ClassPropertyAssignmentIRInjectorStrategy;
class ClassPropertySharedValueAssignmentIRInjectorStrategy;
class SharedValueAssignmentIRInjectorStrategy;
class VariableAssignmentIRInjectorStrategy;
class ArrayAccessAssignmentIRInjectorStrategy;
class ArrayAccessSharedValueAssignmentIRInjectorStrategy;
class ObjectAccessAssignmentIRInjectorStrategy;
class ObjectAccessSharedValueAssignmentIRInjectorStrategy;
class TupleAccessAssignmentIRInjectorStrategy;
class TupleAccessSharedValueAssignmentIRInjectorStrategy;
class ModuleAccessAssignmentIRInjectorStrategy;
class ModuleAccessSharedValueAssignmentIRInjectorStrategy;
class ClassStaticPropertyAssignmentIRInjectorStrategy;
class ClassStaticPropertySharedValueAssignmentIRInjectorStrategy;
class IfStatementIRInjectorStrategy;
class WhileStatementIRInjectorStrategy;
class ForInStatementIRInjectorStrategy;
class ExpressionStatementIRInjectorStrategy;
class ProcedureDeclarationIRInjectorStrategy;
class FunctionDeclarationIRInjectorStrategy;
class TypeValueIRInjectorStrategy;
class BlockIRInjectorStrategy;
class ClassIRInjectorStrategy;

class IRInjector : public std::enable_shared_from_this<IRInjector> {
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
    std::shared_ptr<SharedPtrIRInjectorStrategy> _sharedPtrIRInjector;
    std::shared_ptr<LambdaIRInjectorStrategy> _lambdaIRInjector;
    std::shared_ptr<EnumIRInjectorStrategy> _enumIRInjector;
    std::shared_ptr<NewClassInstanceIRInjectorStrategy> _newClassInstanceIRInjectorStrategy;
    std::shared_ptr<ClassInstanceIRInjectorStrategy> _classInstanceIRInjectorStrategy;
    std::shared_ptr<VariableIRInjectorStrategy> _variableIRInjector;
    std::shared_ptr<ModuleIRInjectorStrategy> _moduleIRInjector;
    std::shared_ptr<FunctionParameterIRInjectorStrategy> _functionParameterIRInjector;
    std::shared_ptr<FunctionReturnIRInjectorStrategy> _functionReturnIRInjector;
    std::shared_ptr<ClassPropertyAssignmentIRInjectorStrategy> _classPropertyAssignmentIRInjectorStrategy;
    std::shared_ptr<ClassPropertySharedValueAssignmentIRInjectorStrategy> _classPropertySharedValueAssignmentIRInjectorStrategy;
    std::shared_ptr<SharedValueAssignmentIRInjectorStrategy> _sharedValueAssignmentIRInjectorStrategy;
    std::shared_ptr<VariableAssignmentIRInjectorStrategy> _variableAssignmentIRInjectorStrategy;
    std::shared_ptr<ArrayAccessAssignmentIRInjectorStrategy> _arrayAccessAssignmentIRInjectorStrategy;
    std::shared_ptr<ArrayAccessSharedValueAssignmentIRInjectorStrategy> _arrayAccessSharedValueAssignmentIRInjectorStrategy;
    std::shared_ptr<ObjectAccessAssignmentIRInjectorStrategy> _objectAccessAssignmentIRInjectorStrategy;
    std::shared_ptr<ObjectAccessSharedValueAssignmentIRInjectorStrategy> _objectAccessSharedValueAssignmentIRInjectorStrategy;
    std::shared_ptr<TupleAccessAssignmentIRInjectorStrategy> _tupleAccessAssignmentIRInjectorStrategy;
    std::shared_ptr<TupleAccessSharedValueAssignmentIRInjectorStrategy> _tupleAccessSharedValueAssignmentIRInjectorStrategy;
    std::shared_ptr<ModuleAccessAssignmentIRInjectorStrategy> _moduleAccessAssignmentIRInjectorStrategy;
    std::shared_ptr<ModuleAccessSharedValueAssignmentIRInjectorStrategy> _moduleAccessSharedValueAssignmentIRInjectorStrategy;
    std::shared_ptr<ClassStaticPropertyAssignmentIRInjectorStrategy> _classStaticPropertyAssignmentIRInjectorStrategy;
    std::shared_ptr<ClassStaticPropertySharedValueAssignmentIRInjectorStrategy> _classStaticPropertySharedValueAssignmentIRInjectorStrategy;
    std::shared_ptr<IfStatementIRInjectorStrategy> _ifStatementIRInjectorStrategy;
    std::shared_ptr<WhileStatementIRInjectorStrategy> _whileStatementIRInjectorStrategy;
    std::shared_ptr<ForInStatementIRInjectorStrategy> _forInStatementIRInjectorStrategy;
    std::shared_ptr<ExpressionStatementIRInjectorStrategy> _expressionStatementIRInjectorStrategy;
    std::shared_ptr<ProcedureDeclarationIRInjectorStrategy> _procedureDeclarationIRInjectorStrategy;
    std::shared_ptr<FunctionDeclarationIRInjectorStrategy> _functionDeclarationIRInjectorStrategy;
    std::shared_ptr<TypeValueIRInjectorStrategy> _typeValueIRInjectorStrategy;
    std::shared_ptr<BlockIRInjectorStrategy> _blockIRInjectorStrategy;
    std::shared_ptr<ClassIRInjectorStrategy> _classIRInjectorStrategy;
    void init();
    std::pair<TypeSource, std::shared_ptr<IRInjectorStrategy>> insert(TypeSource typeSignature, std::shared_ptr<IRInjectorStrategy> injector);
public:
    IRInjector();
    void inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRNode> irNode, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    void inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRDeclarationNode> irDeclaration, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    void inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRStatementNode> irStatement, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    void inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRBlockNode> irNode, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRType> irType, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    void injectVoidReturnType(std::shared_ptr<IRBlockNode> irBlock);
    llvm::Value* injectStringGlobalVariable(std::shared_ptr<IRBlockNode> irBlock, std::string id, std::string rawString, std::shared_ptr<IRModuleNode> irModule);
    llvm::AllocaInst* injectRawString(std::shared_ptr<IRBlockNode> irBlock, std::string rawString);
};

#endif //JETLANG_IR_INJECTOR_H
