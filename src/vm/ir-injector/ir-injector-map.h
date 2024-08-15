//
// Created by Johny Georges on 2024-08-12.
//

#ifndef JETLANG_IR_INJECTOR_MAP_H
#define JETLANG_IR_INJECTOR_MAP_H

#include <unordered_map>
#include "../ir-type/ir-type.h"
#include "../../core/type-signature/types/type-source.h"
#include "../../core/type-signature/type-signature.h"
#include "ir-injectors/ir-injector.h"
#include "ir-injectors/string-ir-injector/string-ir-injector.h"
#include "ir-injectors/array-ir-injector/array-ir-injector.h"
#include "ir-injectors/literal-ir-injector/literal-ir-injector.h"
#include "ir-injectors/struct-ir-injector/struct-ir-injector.h"
#include "ir-injectors/tuple-ir-injector/tuple-ir-injector.h"


class IRInjectorMap {
private:
    std::unordered_map<TypeSource, ExpressionIRInjector*, std::hash<int>> _injectorMap;
    StringIRInjector* _stringIRInjector;
    LiteralIRInjector* _literalIRInjector;
    ArrayIRInjector* _arrayIRInjector;
    StructIRInjector* _structIRInjector;
    TupleIRInjector* _tupleIRInjector;
    void init();
    std::pair<TypeSource, ExpressionIRInjector*> insert(TypeSource typeSignature, ExpressionIRInjector* injector);
public:
    IRInjectorMap();
    StringIRInjector* getStringInjector();
    ArrayIRInjector* getArrayInjector();
    StructIRInjector* getStructInjector();
    LiteralIRInjector* getLiteralInjector();
    TupleIRInjector* getTupleInjector();
    ExpressionIRInjector* getInjector(TypeSignature* typeSignature);
};

#endif //JETLANG_IR_INJECTOR_MAP_H
