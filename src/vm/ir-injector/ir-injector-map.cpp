//
// Created by Johny Georges on 2024-08-12.
//

#include "ir-injector-map.h"

IRInjectorMap::IRInjectorMap() {
    _injectorMap = std::unordered_map<TypeSource, IRInjector*, std::hash<int>>();
    _stringIRInjector = new StringIRInjector(this);
    _arrayIRInjector = new ArrayIRInjector(this);
    this->init();
}

void IRInjectorMap::init() {
    _injectorMap.insert(this->insert(STRING_LITERAL_TYPE_SOURCE, _stringIRInjector));
    _injectorMap.insert(this->insert(ARRAY_TYPE_SOURCE, _arrayIRInjector));
}

std::pair<TypeSource, IRInjector*> IRInjectorMap::insert(TypeSource typeSignature, IRInjector* injector) {
    return std::pair { typeSignature, injector };
}

IRInjector* IRInjectorMap::getInjector(TypeSignature* typeSignature) {
    auto injector = _injectorMap.find(typeSignature->getTypeTarget());
    if (injector == _injectorMap.end()) {
        throw std::invalid_argument("unable to find injector for type signature: " + typeSignature->toString());
    }
    return injector->second;
}

StringIRInjector* IRInjectorMap::getStringInjector() {
    return _stringIRInjector;
}

ArrayIRInjector* IRInjectorMap::getArrayInjector() {
    return _arrayIRInjector;
}