# Determinization of Finite Automata
The algorithm for the determinization of 
a finite automaton is a fundamental tool in 
the theory of formal languages. 
It has widespread practical applications in 
text processing, data analysis, and various 
fields of computer science. This algorithm is
particularly valuable in converting 
nondeterministic automata into deterministic 
ones, enabling efficient language analysis.

### Task Description
The task is to implement the determinization
algorithm as a function in C++. 
The function signature should be:

```DFA determinize(const MISNFA &nfa);```

The input to the algorithm is a nondeterministic 
finite automaton with multiple initial states
**MISNFA**, and the output is a deterministic 
finite automaton **DFA**. The structures
**MISNFA** and **DFA** are defined in the testing environment and represent the respective automata.

### Input Constraints
* Sets of states **MISNFA::m_States**, initial states **MISNFA::m_InitialStates**
and alphabet symbols **MISNFA::m_Alphabet** will be non-empty.
* Initial and final states from the sets 
**MISNFA::m_InitialStates** and **MISNFA::m_FinalStates**
will also be elements of the set of states **MISNFA::m_States**.
* If there is no defined transition for a state 
q and an alphabet symbol in the automaton, then in the map 
**MISNFA::m_Transitions**, the key **(q, a)** 
will not have an empty set as its value, but this 
key will not exist at all.
* The transitions map **MISNFA::m_Transitions**
will only contain elements specified in the set of alphabet symbols and states.

### Output Constraints
The resulting DFA must meet the conditions of the
automaton definition. The same requirements apply 
as for **MISNFA**, except for obvious changes due to different definitions of the initial state and transition function.

### Special Cases
In case the language of the automaton is empty, submit a single-state automaton over the same alphabet as the original automaton.

### Implementation Details
* **Data Structures Used:**
    - `std::set`: Used to represent sets of states and symbols in the `MISNFA` and `DFA` structures.
    - `std::map`: Utilized in `MISNFA` and `DFA` to store state transitions.
    - `std::queue`: Used for Breadth-First Search (BFS) in the `unreachable_removal` and `determinize` methods.
* **Algorithm Overview:**

  - `unreachable_removal`: Performs a Breadth-First Search (BFS) to find and remove unreachable states in the NFA.

  - `find_useful`: Helper method for `redundant_removal` to identify useful states by analyzing transitions.

  - `redundant_removal`: Removes redundant states by finding and keeping only the necessary states.

  - `determinize`: Converts the NFA to a DFA using the powerset construction algorithm.
* **Functionality:**

    - `NFA::unreachable_removal`: Removes unreachable states from the NFA, improving efficiency.

    - `NFA::redundant_removal`: Eliminates redundant states from the NFA, optimizing the automaton.

    - `NFA::determinize`: Transforms the NFA into an equivalent DFA, simplifying further analysis.
* **Code Structure:**

    - The code is organized into functions and structures, facilitating readability and modularity.

    - Meaningful variable and function names are used, enhancing code understandability.

* Submit a source file containing the implementation of the required determinize function.
* Include any additional supporting functions called by determinize in the source file.
* The function will be called from the testing environment, so strictly adhere to the specified function interface.
* Use the provided code as a basis for implementation. Conditional compilation blocks are included; please keep them in the submitted source file.
### Testing
A sample file is provided for download, containing basic tests. Adjustments may be necessary as test results depend on the reference solutions. Your program will run in a restricted testing environment, limited by runtime and available memory size.

### Example

```cpp

int main() {
    // Define an example MISNFA
    MISNFA nfa = { /* ... */ };

    // Convert NFA to DFA
    DFA dfa = determinize(nfa);

    // Additional operations (e.g., unreachable state removal, redundant state removal) can be applied
    // ...

    return 0;
}