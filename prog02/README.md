# Ancient Civilization Language Analysisq

### Task Description
During an exploration of the remotest place on our planet, remnants of an ancient civilization were discovered, carefully hidden in the dark depths of caves. Among these rare finds, clay tablets with mysterious texts were found, the meaning of which remains shrouded in mystery. Strangely, each tablet appears to be written in a different language.

University professors faced the challenge: determine which language corresponds to the texts on each tablet. To unravel this mystery, they gathered information about all possible languages in which the texts could be written. These languages were formally described using grammars.

To facilitate the automatic processing of these languages, the professors proposed a standardized representation of all rules and converted the grammars into this unified form. This representation allows rewriting the left side of a rule into two non-terminals or one terminal. If needed for generating an empty word, a rule is allowed to overwrite the initial non-terminal with nothing, but the initial non-terminal must not appear on the right side of any rule in this grammar.

The following night was dedicated to transcribing symbols from the clay tablets. To our immense pleasure, this ancient civilization used a set of symbols that precisely corresponds to the symbols in ASCII encoding. This allowed us to easily convert the symbols into a modern form and process them by computers.

However, the university lacks skilled programmers, so they are seeking help. The university is looking for those who can write a program to determine whether a given word belongs to the language represented by the grammars described above. In the case of a positive answer, it is also necessary to find a way to create this word according to the rules of the grammar.

## Implementation

Task is to implement this as a C++ program function with the signature: `std::vector<size_t> trace(const Grammar&, const Word&);`. The function takes as input the language grammar (represented as a Grammar structure) and a word (Word) to determine if it belongs to the language. These structures are defined in the test environment, see the sample file. The grammar is defined in the standard way as in the lectures. For simplicity, grammar symbols are defined as any values of type char. If the word belongs to the language, return a sequence of indices of the rules from which it was derived by successive derivation of the leftmost non-terminal. Rules are numbered starting from zero. If the word does not belong to the language, return an empty sequence.

It is guaranteed that the input will be a valid grammar with rules according to the assignment:

- The sets of symbols (Grammar::m_Terminals, Grammar::m_Nonterminals) will have no intersection.
- All rules will contain only symbols from these two sets.
- All rules will have exactly one terminal, two non-terminals, or, if the left side is the initial non-terminal, nothing on the right side (but then the initial non-terminal must not appear on the right side of any other rule in this grammar).
- The initial symbol of the grammar will appear in the set of non-terminals.
- There will be no duplicates among the rules.


In the hints, the input format is a sequence of symbols separated by spaces, i.e., "a b" is represented as Word{'a', 'b'}.

### Input Constraints
#### Valid Grammar
The input grammar must adhere to certain constraints:

* Non-terminals and terminals sets must have no intersection.
* Rules must contain symbols only from the non-terminals and terminals sets.
* Rules can have one terminal, two non-terminals, or, if the left side is the initial non-terminal, nothing on the right side.
* The initial symbol of the grammar must be present in the set of non-terminals.
* There should be no duplicates among the rules.

### Output Constraints
#### Returned Indices
The trace function returns a vector of indices
representing the derivation of the input word.
These indices correspond to the rules applied
during the derivation process.

#### Empty Result
If the input word does not belong to the language
represented by the grammar, the function returns
an empty vector.

### Special Cases
#### Empty Word
When the input word is empty, the trace function checks if there exists a rule with the initial symbol generating an empty word. If found, the corresponding rule index is returned.

#### Single-Symbol Words
For words consisting of a single symbol, the trace function directly searches for rules matching the symbol, considering both non-terminals and terminals.

#### Invalid Input
The program handles cases where the input grammar does not adhere to the specified constraints. It assumes a valid grammar structure as described in the task.


### Header Files

The program includes the following standard C++ header files:

```cpp
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>
```

### Type Aliases
The program defines the following type aliases:
```cpp
using Symbol = char;
using Word = std::vector<Symbol>;
```

### Implementation Details
#### Grammar Structure
The Grammar structure represents the grammar used in language analysis. It includes sets of non-terminals and terminals, along with a vector of rules, each consisting of a non-terminal and a vector of symbols. The initial symbol of the grammar is also specified.
```cpp
struct Grammar {
std::set<Symbol> m_Nonterminals;
std::set<Symbol> m_Terminals;
std::vector<std::pair<Symbol, std::vector<Symbol>>> m_Rules;
Symbol m_InitialSymbol;
};
```

#### Trace Function
The trace function is the main entry point for the program. It takes a grammar and a word as input and returns a vector of indices representing the derivation of the word according to the grammar rules.
```cpp
std::vector<size_t> trace(const Grammar& grammar, const Word& word);
```

#### Decoding Logic
The decoding logic is encapsulated in the 
Decoder structure. 
It includes methods for decoding 
substrings
and tracing the derivation of words in the 
grammar. The trace function uses an instance 
of Decoder to perform the language analysis.

```cpp
struct Decoder {
struct Element {
Element();
set<Symbol> symbols;
set<size_t> rules;
};

    using iterator = std::map<std::string, Element>::iterator;
    Decoder(const Grammar *g);
    auto &operator[](const std::string &key);
    std::pair<iterator, bool> emplace(const std::string &word, const Element &element);
    void cartesian(const Decoder::Element &A, const Decoder::Element &B, Element &result) const;
    Element decodeSubstr(const std::string &word);
    void calculateCases(const std::string &word);
    vector<size_t> calculateTrace(const std::string &word, const size_t &symbol, const vector<size_t> &result);
    void decodeSymbols();

    const Grammar *grammar;
    std::map<std::string, Element> substr_decoder;
    std::map<Symbol, set<size_t>> symbol_decoder;
};
```
#### Creating new element by decoding the Cartesian Product of two decoder elements
The cartesian decoding method in the Decoder 
structure calculates the Cartesian product of two
sets of symbols, which is crucial for efficient 
language analysis. It utilizes the grammar rules 
to determine valid combinations.

#### Trace Calculation
The calculateTrace method in the Decoder 
structure recursively traces the derivation 
of a word based on grammar rules. 
It considers possible rules and their 
combinations to identify valid derivations.


