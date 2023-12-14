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