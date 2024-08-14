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


class IRInjectorMap {
private:
    std::unordered_map<TypeSource, IRInjector*, std::hash<int>> _injectorMap;
    StringIRInjector* _stringIRInjector;
    ArrayIRInjector* _arrayIRInjector;
    void init();
    std::pair<TypeSource, IRInjector*> insert(TypeSource typeSignature, IRInjector* injector);
public:
    IRInjectorMap();
    StringIRInjector* getStringInjector();
    ArrayIRInjector* getArrayInjector();
    IRInjector* getInjector(TypeSignature* typeSignature);
};

#endif //JETLANG_IR_INJECTOR_MAP_H
