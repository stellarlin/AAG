#ifndef __PROGTEST__
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

using namespace std;
using Symbol = char;
using Word = std::vector<Symbol>;

struct Grammar {
    std::set<Symbol> m_Nonterminals;
    std::set<Symbol> m_Terminals;
    std::vector<std::pair<Symbol, std::vector<Symbol>>> m_Rules;
    Symbol m_InitialSymbol;
};
#endif


struct Row
{
    std::map<size_t,set<Symbol>>::iterator begin () { return  columns.begin();}
    std::map<size_t,set<Symbol>>::iterator end () { return  columns.end();}

    bool empty () const { return columns.empty();}

    std::map<size_t,set<Symbol>> columns;

};


struct Table
{
    std::map<size_t, Row> rows;

    std::map<size_t, Row>::iterator begin () { return  rows.begin();}
    std::map<size_t, Row>::iterator end () { return  rows.end();}

    void insert ( const set<Symbol> & src,  size_t row, size_t col);
    auto & cell (size_t row, size_t col) {return rows[row].columns[col];}

    bool empty () const { return rows.empty();}

};

void Table::insert(const set<Symbol> &src, size_t row, size_t col) {
    auto & dest = cell(row,col);
    dest.insert( src.begin(), src.end());
}

struct Decoder
        {
    struct Element {
        Element() = default;
        set<Symbol> symbols;
        set<size_t> rules;
    };

    using iterator = std::map<std::string, Element>::iterator;
    Decoder (const Grammar * g) : grammar (g) {}

    auto & operator [] (const std::string & key) { return substr_decoder[key];}
    std::pair<iterator, bool>  emplace (const std::string & word, const Element & element);
    void cartesian(const Decoder::Element & A, const Decoder::Element & B, Element & result) const;
    Element decodeSubstr (const std::string & word);
    void calculateCases ( const std::string & word);
    vector<size_t> calculateTrace(const std::string & word, const size_t & symbol,  const vector<size_t> & result);
    void decodeSymbols ();

    const Grammar * grammar;
    std::map<std::string, Element> substr_decoder;
    std::map<Symbol , set<size_t>> symbol_decoder;

};


void Decoder::cartesian(const Decoder::Element & A, const Decoder::Element & B, Element & result) const {

    if(A.symbols.empty() || B.symbols.empty()) return;

    std::set<std::vector<Symbol>> CartRules;
    // Iterate over the cartesian product of A and B
    for (const Symbol& a : A.symbols) {
        for (const Symbol& b : B.symbols) {
            CartRules.insert({a,b});
        }
    }

    size_t rule_idx = 0;
    for(const auto & [nonTerminal, rule] : grammar->m_Rules) {
        if (CartRules.find(rule) != CartRules.end()) {
            result.symbols.emplace(nonTerminal);
            result.rules.emplace(rule_idx);
        }
        ++rule_idx;
    }
}


Decoder::Element Decoder::decodeSubstr (const std::string & word)
{
    Element  result;
    if(word.size() == 1)
    {
        size_t rule_idx = 0;
        // Iterate over the grammar rules
        for (const auto & [nonTerminal, rule] : grammar->m_Rules) {

            // Check if the rule has only one element and it's equal to s
            if (rule.size() == 1 && rule[0] == word[0]) {
                result.symbols.emplace(nonTerminal);
                result.rules.emplace(rule_idx);
            }
            ++rule_idx;
        }
    }
    else
    {
        for (size_t len = 1; len < word.size(); len++)
            cartesian(substr_decoder[word.substr(0, len)],
                             substr_decoder[word.substr(len)], result);
    }

    return result;
}

std::pair<Decoder::iterator, bool> Decoder::emplace(const std::string & word, const Decoder::Element &element) {
    return substr_decoder.emplace(word, element);
}

void Decoder::calculateCases(const std::string &word) {
    for (size_t length = 1; length <= word.size(); length++)
    {
        for (size_t start = 0; start < word.size(); start ++)
        {
            auto sub_word = word.substr( start, length);
            if(sub_word.empty() || sub_word.size() < length) break;

            const auto & [sub_decoded, flag] = emplace(sub_word, {});
            auto & [sub_key, sub_value] = *sub_decoded;
            if (flag)  sub_value = decodeSubstr(sub_word);
        }
    }
}

void Decoder::decodeSymbols() {
    size_t idx = 0;
    for (const auto & [nonTermintal, rule] : grammar->m_Rules)
    {
        symbol_decoder[nonTermintal].emplace(idx++);
    }
}

vector<size_t> Decoder::calculateTrace(const string &word, const size_t &symbol, const vector<size_t> & prev)  {

    auto & word_rules = substr_decoder[word].rules;
    auto & symbol_rules = symbol_decoder[symbol];

    set<size_t> possible_rules;
    std::set_intersection(word_rules.begin(), word_rules.end(),
                          symbol_rules.begin(),symbol_rules.end(),
                          std::inserter(possible_rules, possible_rules.begin()));
    if (possible_rules.empty()) return {};


    for (const auto & rule_num : possible_rules)
    {
        auto result = prev;
        result.push_back(rule_num);
        auto & [nonTerm, rule] = grammar->m_Rules[rule_num];
        if (rule.size() == 1)
        {
            if(word.size() == 1)return result;
            else continue;
        }
        for (size_t len = 1; len < word.size(); ++len)
        {
            //part1
            auto part1 = calculateTrace(word.substr(0, len), rule[0], result);
            if (part1.empty()) continue;

            //part2
            auto part2 = calculateTrace(word.substr(len), rule[1], part1);
            if (part2.empty()) continue;

            return part2;
        }
    }
    return {};
}


std::vector<size_t> trace(const Grammar& grammar, const Word& word)
{
    std::string word_str(word.begin(), word.end());
    vector<size_t> res;

    if (word_str.empty())
    {

        // Find the pair {S, {}} in m_Rules
        auto it = std::find_if(grammar.m_Rules.begin(), grammar.m_Rules.end(),
                               [&grammar](const auto& rule)
                               { return rule.first == grammar.m_InitialSymbol && rule.second.empty(); });
        // Check if the iterator was found
        if (it != grammar.m_Rules.end()) res.push_back(std::distance(grammar.m_Rules.begin(), it));
    }
    else
    {
        Decoder decoder(&grammar);
        decoder. calculateCases(word_str);

        decoder.decodeSymbols();

        res =  decoder.calculateTrace(word_str, grammar.m_InitialSymbol, {});
    }

    return res;
}

#ifndef __PROGTEST__
int main()
{
    Grammar g0{
        {'A', 'B', 'C', 'S'},
        {'a', 'b'},
        {
            {'S', {'A', 'B'}},
            {'S', {'B', 'C'}},
            {'A', {'B', 'A'}},
            {'A', {'a'}},
            {'B', {'C', 'C'}},
            {'B', {'b'}},
            {'C', {'A', 'B'}},
            {'C', {'a'}},
        },
        'S'};

    assert(trace(g0, {'b', 'a', 'a', 'b', 'a'}) == std::vector<size_t>({0, 2, 5, 3, 4, 6, 3, 5, 7}));
    assert(trace(g0, {'b'}) == std::vector<size_t>({}));
    assert(trace(g0, {'a'}) == std::vector<size_t>({}));
    assert(trace(g0, {}) == std::vector<size_t>({}));
 //   assert(trace(g0, {'a', 'a', 'a', 'a', 'a'}) == std::vector<size_t>({1, 4, 6, 3, 4, 7, 7, 7, 7}));
    assert(trace(g0, {'a', 'b'}) == std::vector<size_t>({0, 3, 5}));
    assert(trace(g0, {'b', 'a'}) == std::vector<size_t>({1, 5, 7}));
    assert(trace(g0, {'c', 'a'}) == std::vector<size_t>({}));

    Grammar g1{
        {'A', 'B'},
        {'x', 'y'},
        {
            {'A', {}},
            {'A', {'x'}},
            {'B', {'x'}},
            {'A', {'B', 'B'}},
            {'B', {'B', 'B'}},
        },
        'A'};

    assert(trace(g1, {}) == std::vector<size_t>({0}));
    assert(trace(g1, {'x'}) == std::vector<size_t>({1}));
    assert(trace(g1, {'x', 'x'}) == std::vector<size_t>({3, 2, 2}));
//    assert(trace(g1, {'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2}));

    Grammar g2{
        {'A', 'B'},
        {'x', 'y'},
        {
            {'A', {'x'}},
            {'B', {'x'}},
            {'A', {'B', 'B'}},
            {'B', {'B', 'B'}},
        },
        'B'};

    assert(trace(g2, {}) == std::vector<size_t>({}));
    assert(trace(g2, {'x'}) == std::vector<size_t>({1}));
    assert(trace(g2, {'x', 'x'}) == std::vector<size_t>({3, 1, 1}));
    assert(trace(g2, {'x', 'x', 'x'}) == std::vector<size_t>({3, 3, 1, 1, 1}));

    Grammar g3{
        {'A', 'B', 'C', 'D', 'E', 'S'},
        {'a', 'b'},
        {
            {'S', {'A', 'B'}},
            {'S', {'S', 'S'}},
            {'S', {'a'}},
            {'A', {'B', 'S'}},
            {'A', {'C', 'D'}},
            {'A', {'b'}},
            {'B', {'D', 'D'}},
            {'B', {'b'}},
            {'C', {'D', 'E'}},
            {'C', {'b'}},
            {'C', {'a'}},
            {'D', {'a'}},
            {'E', {'S', 'S'}},
        },
        'S'};

    assert(trace(g3, {}) == std::vector<size_t>({}));
    assert(trace(g3, {'b'}) == std::vector<size_t>({}));
    assert(trace(g3, {'a', 'b', 'a', 'a', 'b'}) == std::vector<size_t>({1, 2, 0, 3, 7, 1, 2, 2, 7}));
    assert(trace(g3, {'a', 'b', 'a', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'a'}) == std::vector<size_t>({1, 1, 0, 4, 8, 11, 12, 0, 5, 6, 11, 11, 0, 4, 9, 11, 7, 11, 7, 2, 2}));
}
#endif

