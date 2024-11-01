//
// Created by Johny Georges on 2024-08-12.
//

#ifndef JETLANG_IR_INJECTOR_MAP_H
#define JETLANG_IR_INJECTOR_MAP_H

#include <unordered_map>
#include "../ir-type/ir-type.h"
#include "../../core/type-signature/types/type-source.h"
#include "../../core/type-signature/type-signature.h"
#include "ir-injector-strategies/ir-injector-strategy.h"
#include "ir-injector-strategies/string-ir-injector-strategy/string-ir-injector-strategy.h"
#include "ir-injector-strategies/literal-ir-injector-strategy/literal-ir-injector-strategy.h"
#include "ir-injector-strategies/array-ir-injector-strategy/array-ir-injector-strategy.h"
#include "ir-injector-strategies/struct-ir-injector-strategy/struct-ir-injector-strategy.h"
#include "ir-injector-strategies/tuple-ir-injector-strategy/tuple-ir-injector-strategy.h"
#include "ir-injector-strategies/variable-ir-injector-strategy/variable-ir-injector-strategy.h"
#include "ir-injector-strategies/function-return-ir-injector-strategy/function-return-ir-injector-strategy.h"
#include "../types/ir-operation-type.h"
#include "ir-injector-strategies/function-parameter-ir-injector-strategy/function-parameter-ir-injector-strategy.h"
#include "ir-injector-strategies/module-ir-injector-strategy/module-ir-injector-strategy.h"


class IRInjectorMap {
private:
    std::unordered_map<TypeSource, IRInjectorStrategy*, std::hash<int>> _injectorMap;
    StringIRInjectorStrategy* _stringIRInjector;
    LiteralIRInjectorStrategy* _literalIRInjector;
    ArrayIRInjectorStrategy* _arrayIRInjector;
    StructIRInjectorStrategy* _structIRInjector;
    TupleIRInjectorStrategy* _tupleIRInjector;
    VariableIRInjectorStrategy* _variableIRInjector;
    ModuleIRInjectorStrategy* _moduleIRInjector;
    FunctionParameterIRInjectorStrategy* _functionParameterIRInjector;
    FunctionReturnIRInjectorStrategy* _functionReturnIRInjector;
    void init();
    std::pair<TypeSource, IRInjectorStrategy*> insert(TypeSource typeSignature, IRInjectorStrategy* injector);
public:
    IRInjectorMap();
    StringIRInjectorStrategy* getStringInjector();
    ArrayIRInjectorStrategy* getArrayInjector();
    StructIRInjectorStrategy* getStructInjector();
    LiteralIRInjectorStrategy* getLiteralInjector();
    TupleIRInjectorStrategy* getTupleInjector();
    VariableIRInjectorStrategy* getVariableInjector();
    ModuleIRInjectorStrategy* getModuleInjector();
    FunctionParameterIRInjectorStrategy* getFunctionParameterInjector();
    FunctionReturnIRInjectorStrategy* getFunctionReturnInjector();
    IRInjectorStrategy* getInjector(TypeSignature* typeSignature);
};

#endif //JETLANG_IR_INJECTOR_MAP_H
