//
// Created by Johny Georges on 2024-11-04.
//

#ifndef JETLANG_JET_FILE_H
#define JETLANG_JET_FILE_H

#include <set>
#include "../ast/ast-nodes/ast-file-node.h"
#include "../pre-processor/semantic-analyzer/type-signature-lookup-table/type-signature-lookup-table.h"
#include "../pre-processor/semantic-analyzer/type-checker/types/type-checker-result/type-checker-result.h"

class JetFile {
private:
    std::string _id;
    ASTFileNode* _astFileNode;
    TypeSignatureLookupTable* _fileScope;
    TypeCheckerResult _typeCheckerResult;
    std::set<JetFile*> _importedJetFiles;
public:
    JetFile(ASTFileNode* astFileNode, TypeSignatureLookupTable* fileScope, TypeCheckerResult typeCheckerResult, std::set<JetFile*> importedJetFiles);
    JetFile(ASTFileNode* astFileNode, TypeSignatureLookupTable* fileScope, TypeCheckerResult typeCheckerResult);
    std::string getId();
    ASTFileNode* getFile();
    TypeSignatureLookupTable* getScope();
    TypeCheckerResult* getTypeCheckerResult();
    void inheritImportedFiles(JetFile* jetFile);
    void addImportedFile(JetFile* jetFile);
    std::set<JetFile*>* getImportedFiles();
    bool isModule();
    void print();
};

#endif //JETLANG_JET_FILE_H
