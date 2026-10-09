// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-02-15.
//

#ifndef JETLANG_DFA_NODE_OCCURRENCE_H
#define JETLANG_DFA_NODE_OCCURRENCE_H
typedef enum {
    DFA_OCCURRENCE_ONCE,
    DFA_OCCURRENCE_ONCE_OR_MORE,
    DFA_OCCURRENCE_NIL_OR_MORE,
    DFA_OCCURRENCE_NIL_OR_ONCE,
} DFANodeOccurrence;
#endif //JETLANG_DFA_NODE_OCCURRENCE_H
