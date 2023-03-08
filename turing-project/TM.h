#include<iostream>
#include<string.h>
#include<vector>
#include <iomanip> 

#include<fstream>
#include<assert.h>
#include<regex>

using namespace std;

class TuringMachine{
 private: 
    enum {STATES, INPUT, TAPE, FINALS, DELTA} kind;
    bool verbose;
    char* fileName;
    vector<string> Q, F;
    vector<char> S, G;
    string q0;
    char B;
    int N;
    struct State{
        string old_states, old_syms, new_syms, new_dires, new_states; 
    };
    vector<State> delta;

    vector<vector<char>> tape;//2n
    vector<int> index;

    State cur;
    int step;
 public: 
    TuringMachine(const char* fileName, const bool v);
    ~TuringMachine();   
    void resolver();
    void simulator(const char* str);
    void verboseINFO(const char* seg, const char* info);
    template<typename T>
    void getVector(string str, vector<T> v, int kind);
    void deleteAllSpace(string &s);
    void callErr(string read);
    void printState();
    char* itos(const int x);
    void print();
};


