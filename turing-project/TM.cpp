// #define DEBUG
#include "TM.h"
TuringMachine::TuringMachine(const char* fileName, const bool v){
    this->fileName = new char[strlen(fileName)+1];
    strcpy(this->fileName, fileName);
    verbose = v;
}
char* TuringMachine::itos(const int x){
  char* str = new char[100];

  if(x<10){
    str[0]=x+'0';
    str[1]=0;
    return str;
  }

  int i,t=x;
  for(i=0; t > 0; t/=10, i++){
    str[i]=t%10+'0';
  }
  char c;
  for(int j = 0; j*2<i; j++){
    c = str[j];
    str[j]=str[i-j-1];
    str[i-j-1]=c;
  }
  str[i+1]=0;
  return str;
}
void TuringMachine::deleteAllSpace(string &s)
{
    string delim(" ");
	size_t nSize = delim.size();
	while(1)
	{
		size_t pos = s.find(delim);    //  尤其是这里
		if(pos == string::npos)
		{
			return;
		}
 
		s.erase(pos, nSize);
	}
}
template<typename T>
void TuringMachine::getVector(string str, vector<T> v, int kind){
    switch (kind){
    case STATES:{
        int lc = str.find('{');
        int rc = str.rfind('}');
        string tmp(str, lc+1, rc-lc-1);

        smatch result;
        regex pattern0("[^\\w,]");
        if(regex_search(tmp, pattern0)){//match except [a-Z0-9,]
            // cout << "ERROR" << endl;
            cerr << "syntax error1" << endl;
            exit(-1);
        }
        regex pattern("[\\w]+");
        string::const_iterator it = tmp.begin();

        string::const_iterator iterStart = tmp.begin();
        string::const_iterator iterEnd = tmp.end();
        string temp;
        int idx = 0;
        #ifdef DEBUG
        cout << tmp << endl;
        #endif
        while (regex_search(iterStart, iterEnd, result, pattern)){//get every str
            temp = result[0];
            Q.push_back(temp);//store the str in Q
            #ifdef DEBUG
            cout << temp << " ";
            #endif
            iterStart = result[0].second;	//更新搜索起始位置,搜索剩下的字符串       
        }
        #ifdef DEBUG
        cout << endl;
        #endif
        /* code */
        break;
    }
    case INPUT:{// a lot of chars
        int lc = str.find('{');
        int rc = str.rfind('}');
        string tmp(str, lc+1, rc-lc-1);
        //split the char by , 
        smatch result;
        regex pattern0("[;\\*_\\{\\}]");
        if(regex_search(tmp, pattern0)){//match except [a-Z0-9,]
            // cout << "ERROR" << endl;
            cerr << "syntax error2" << endl;
            exit(-1);
        }
        regex pattern("[^,;\\*_\\{\\}]");
        string::const_iterator it = tmp.begin();
        string::const_iterator iterStart = tmp.begin();
        string::const_iterator iterEnd = tmp.end();
        string temp;
        int idx = 0;
        #ifdef DEBUG
        cout << tmp << endl;
        #endif
        while (regex_search(iterStart, iterEnd, result, pattern)){//get every char
            temp = result[0];
            S.push_back(temp[0]);//store the str in Q
            #ifdef DEBUG
            cout << temp << " ";
            #endif
            iterStart = result[0].second;	//更新搜索起始位置,搜索剩下的字符串
        }
        #ifdef DEBUG
        cout << endl;
        #endif
        break;
    }
    case TAPE:{
        int lc = str.find('{');
        int rc = str.rfind('}');
        string tmp(str, lc+1, rc-lc-1);
        //split the char by , 
        smatch result;
        regex pattern0("[;\\*\\{\\}]");
        if(regex_search(tmp, pattern0)){//match except [a-Z0-9,]
            // cout << "ERROR" << endl;
            cerr << "syntax error3" << endl;
            exit(-1);
        }
        regex pattern("[^,;\\*\\{\\}]");
        string::const_iterator it = tmp.begin();
        string::const_iterator iterStart = tmp.begin();
        string::const_iterator iterEnd = tmp.end();
        string temp;
        int idx = 0;
        #ifdef DEBUG
        cout << tmp << endl;
        #endif
        while (regex_search(iterStart, iterEnd, result, pattern)){//get every char
            temp = result[0];
            G.push_back(temp[0]);//store the str in Q
            #ifdef DEBUG
            cout << temp << " ";
            #endif
            iterStart = result[0].second;	//更新搜索起始位置,搜索剩下的字符串
        }
        #ifdef DEBUG
        cout << endl;
        #endif
        break;
    }
    case FINALS:{
        int lc = str.find('{');
        int rc = str.rfind('}');
        string tmp(str, lc+1, rc-lc-1);

        smatch result;
        regex pattern0("[^\\w,]");
        if(regex_search(tmp, pattern0)){//match except [a-Z0-9,]
            // cout << "ERROR" << endl;
            cerr << "syntax error4" << endl;
            exit(-1);
        }
        regex pattern("[\\w]+");
        string::const_iterator it = tmp.begin();
        string::const_iterator iterStart = tmp.begin();
        string::const_iterator iterEnd = tmp.end();
        string temp;
        int idx = 0;
        #ifdef DEBUG
        cout << tmp << endl;
        #endif
        while (regex_search(iterStart, iterEnd, result, pattern)){//get every str
            temp = result[0];
            if(find(Q.begin(), Q.end(), temp)==Q.end()){//not in the states set
                cerr << "syntax error5" << endl;
                exit(-1);
            }
            F.push_back(temp);//store the str in Q
            #ifdef DEBUG
            cout << temp << " ";
            #endif
            iterStart = result[0].second;	//更新搜索起始位置,搜索剩下的字符串        
            }
        #ifdef DEBUG
        cout << endl;
        #endif
        break;
    }
    case DELTA:{
        State st;
        #ifdef DEBUG
        cout << "str: #" << str << "#" << endl;
        // cout << "INFO: " << endl;
        #endif
        istringstream readIn(str);
        readIn >> st.old_states >> st.old_syms >> st.new_syms >> st.new_dires >> st.new_states; 
        if(st.old_states.size()==0)
            break;
        if(find(Q.begin(), Q.end(), st.old_states)==Q.end() || find(Q.begin(), Q.end(), st.new_states)==Q.end()){
            cerr << st.old_states << "#" << st.new_states << "#"<< st.new_syms << "#" <<  st.new_dires << "#" << st.new_states << endl;
            cerr << "syntax error6 #" << st.old_states << "#" << st.new_states << "#" << endl;
            // cerr << "@@@@@@" << endl;
            exit(-1);
        }
        int sz = st.old_syms.size();
        int i = 0;
        for(i = 0; i < sz; i++){
            if(st.old_syms[i]!='*' && st.old_syms[i]!='_' && find(G.begin(), G.end(), st.old_syms[i])==G.end()){
                // cout << 
                cerr << "syntax error7" << endl;
                exit(-1);                
            }
        }
        sz = st.new_syms.size();
        for(i = 0; i < sz; i++){
            if(st.new_syms[i]!='*' && st.new_syms[i]!='_' && find(G.begin(), G.end(), st.new_syms[i])==G.end()){
                cerr << "syntax error8" << endl;
                exit(-1);                
            }            
        }
        sz = st.new_dires.size();
        for(i = 0; i < sz; i++){
            if(st.new_dires[i]!='l'&&st.new_dires[i]!='r'&&st.new_dires[i]!='*'){
                cerr << "syntax error9" << endl;
                exit(-1);                   
            }
        }
        delta.push_back(st);
        break;
    }
    default:
        break;
    }
}
void TuringMachine::verboseINFO(const char* seg, const char* info){
    if(verbose){
        cerr << fileName << " " << info << endl;
    }
    cerr << "syntax error10" << endl;
    exit(-1);
}
void TuringMachine::callErr(string read){
    if(read.find('{')==string::npos || read.find('}')==string::npos){
        if(verbose){
            cerr << "read error: " << read << endl;
        }
        cerr << "syntax error" << endl;
        exit(-1);
    }
}
void TuringMachine::resolver(){
    ifstream in_file(fileName, ios::in);
    if(!in_file){
        verboseINFO(fileName, "Not a TuringMachine");
        // callErr();
    }
    string read;
    bool f_Q, f_S, f_G, f_q0, f_B, f_N, f_F;
    f_Q = f_S = f_G = f_q0 = f_B = f_N = f_F = false;
    while(in_file.peek()!=EOF){
        getline(in_file, read);
        if(read.size()==0 || read[0]==';' || read[0]=='\r')
            continue;
        else if(read.find("#Q")==0){
            f_Q  = true;
            callErr(read);
            deleteAllSpace(read);
            getVector(read, Q, STATES);
        }
        else if(read.find("#S")==0){
            f_S = true;
            callErr(read);
            deleteAllSpace(read);
            
            getVector(read, S, INPUT);
        }
        else if(read.find("#G")==0){
            f_G = true;
            callErr(read);
            deleteAllSpace(read);
            
            getVector(read, G, TAPE);
        }
        else if(read.find("#q0")==0){
            //#q0=xxx
            f_q0  = true;
            istringstream readIn(read);
            string tmp;
            readIn >> tmp >> tmp >> q0;
            // deleteAllSpace(read);
            // q0 = read.substr(4);
        }
        else if(read.find("#B")==0){
            //#B=_
            deleteAllSpace(read);
            f_B = true;
            if(read[3]!='_'){

                // cerr << "read size: " << read.size() << "read: " << read << "#" << endl;
                verboseINFO(read.c_str(), "blank symbol error!");
            }
        }
        else if(read.find("#F")==0){
            f_F = true;
            callErr(read);
            getVector(read, F, FINALS);
        }
        else if(read.find("#N")==0){
            //get N
            f_N = true;
            deleteAllSpace(read);
            string num = read.substr(3);
            N = stoi(num);
        }
        else{
        // else if(read.size()!=0)
            if(!f_Q || !f_S || !f_G || !f_q0 || !f_F || !f_N || !f_B){
                if(verbose)
                    cerr << "read: " << read  <<  endl;
                cerr << "syntax error11" << endl;
                exit(-1);
            }
            getVector(read, delta, DELTA);
        }
    }
}
void TuringMachine::print(){
    cout << "###########print TuringMachine##########" << endl;
    cout << "states: " ;
    for(int i = 0; i < Q.size(); i++)
        cout << Q[i] << " " ;
    cout << endl;
    cout << "final states: " ;
    for(int i = 0; i < F.size(); i++)
        cout << F[i] << " " ;
    cout << endl;
    cout << "start state: " << q0 << endl;
    cout << "sigma: " ;
    for(int i = 0; i < S.size(); i++)
        cout << S[i] << " ";
    cout << endl;
    cout << "gama: " ;
    for(int i = 0; i < G.size(); i++)
        cout << G[i] << " ";
    cout << endl;
    cout << "delta: " << endl;
    for(int i = 0; i < delta.size(); i++){
        cout << delta[i].old_states << " " << delta[i].old_syms << " " << delta[i].new_syms
        << " " << delta[i].new_dires << " " << delta[i].new_states << endl;
    }
    cout << "N: " << N << endl;

    cout << "###########print TuringMachine##########" << endl;
}

void TuringMachine::printState(){
    if(verbose){
        cout << std::left << setw(7) <<"Step" << ": " << step << endl;
        cout << std::left << setw(7) <<"State" << ": " << cur.old_states << endl;
        // return;
        // cout << "index[i]: ";
        // for(int i = 0; i < N; i++){
            // cout << index[i] << " " << endl;
        // }
        for(int i = 0; i < N; i++){
            string s="Index";
            // cout << i << " "<< itos(i) << endl;
            char* n=itos(i);
            // cout << n << endl;
            s+=n;
            cout << std::left << setw(7) << s << ": " ;
            int s1 = tape[2*i+1].size();
            int s2 = tape[2*i].size();
            // cout <<endl << s1 << " " << s2 << endl;
            bool find = false;
            int id;
            if(s1 > 1){
                //负索引也有内容
                for(int j = s1 - 1; j > 0; j--){
                    if(!find && -j<index[i]&&tape[2*i+1][j]=='_')
                        continue;
                    if(!find){
                        find = true;
                        id = -j;
                    }
                    cout << j << " " ;
                }
            }
            for(int j=0; j < s2; j++){
                if(!find && j<index[i]&&tape[2*i][j]=='_')
                    continue;
                if(!find){
                    find = true;
                    id = j;
                }
                cout << j << " ";
            }
            cout << endl;

            // cout << "id: " << id << endl;

            s="Tape";
            s+=n;
            cout << std::left << setw(7) << s << ": " ;
            //假设verbose模式下，只会向左向右运行几百个位置
            if(s1>1){
                for(int j = s1-1; j > 99 ; j--){
                    if(-j < id)
                        continue;
                    cout << tape[2*i+1][j] << "   " ;
                }
                for(int j = min(s1-1, 99); j > 9; j--){
                    if(-j < id)
                        continue;
                    cout << tape[2*i+1][j] << "  " ;
                }
                for(int j = min(s1-1, 9); j > 0; j--){
                    if(-j < id)
                        continue;
                    cout << tape[2*i+1][j] << " ";
                }
            }
            for(int j = 0; j < min(10, s2); j++){
                if(j < id)
                    continue;
                cout << tape[2*i][j] << " " ;      
            }      
            for(int j = 10; j < min(100, s2); j++){
                if(j < id)
                    continue;
                cout << tape[2*i][j] << "  " ;
            } 
            for(int j = 100; j < min(1000, s2); j++){
                if(j < id)
                    continue;
                cout << tape[2*i][j] << "   " ; 
            }
            cout << endl;
            s="Head";
            s+=n;
            cout << std::left << setw(7) << s << ": " ;
            //index[i]之前的空格都要打印
            if(s1 > 1){
                for(int j = s1-1; j > 99 && j > -index[i]; j--){
                    if(-j < id)
                        continue;
                    cout << "    " ;
                }
                for(int j = min(s1-1, 99); j > 9 && j > -index[i]; j--){
                    if(-j < id)
                        continue;
                    cout << "   " ;
                }
                for(int j = min(s1-1, 9); j > 0 && j > -index[i]; j--){
                    if(-j < id)
                        continue;
                    cout << "  ";                
                }
            }

            for(int j = 0; j < min(10, s2) && j < index[i]; j++){
                if(j < id)
                    continue;
                cout <<  "  " ;            
            }
            for(int j = 10; j < min(100, s2) && j < index[i]; j++){
                if(j < id)
                    continue;
                cout << "   " ;
            } 
            for(int j = 100; j < min(1000, s2) && j < index[i]; j++){
                if(j < id)
                    continue;
                cout <<  "    " ;            
            }          
            cout << '^' << endl;
        }

        cout << "---------------------------------------------" << endl;
        // cout << std::left << setw(7) <<"Step" << ":" << step << endl;
        // cout << std::left << setw(7) <<"Step" << ":" << step << endl;

    }

// Step   : 0
// State : 0
// Index0 : 0 1 2 3 4 5 6
// Tape0 : 1 0 0 1 0 0 1
// Head0 : ^
// Index1 : 0
// Tape1 : _
// Head1 : ^
// ---------------------------------------------
        
    
}
void TuringMachine::simulator(const char* str){
    // cout << "resolve excessful, simulate " << str << endl;
    //先把整个字符串复制到第一条带上，其他几条带都是空，即
    // print();

    //先检查有没有未定义的字符
    for(int i=0; i < strlen(str); i++){
        if(find(S.begin(), S.end(), str[i])==S.end()){
            //出现了
            if(!verbose){
                cerr << "illegal input" << endl;
                exit(-1);
            }
            else{
                cerr << "Input: " << str << endl;
                cerr << "==================== ERR ====================" << endl;
                cerr << "error: ' " << str[i] << "' was not declared in the set of input symbols" << endl;
                cerr << "Input: " << str << endl;
                cerr << "       " ;
                for(int j = 0; j < i; j++)
                    cerr << " ";
                cerr << "^" << endl;
                cerr << "==================== END ====================" << endl;
                exit(-1);
            } 
        }
    }
    #ifdef DEBUG
    print();
    #endif
    if(verbose){
        cout << "Input: " << str << endl;
        cout << "==================== RUN ====================" << endl;
    }
// Input: 1001001
// ==================== RUN ====================
    tape.resize(2*N);
    index.assign(N, 0);
    for(int i = 0; i < strlen(str); i++){
        tape[0].push_back(str[i]);
    }

    string syms;
    string state;
    state = q0;
    syms.resize(N+1);
    syms[N]='\0';
    if(strlen(str)==0){
        // cout << 1  << endl;;
        tape[0].push_back('_');
    }
    syms[0]=tape[0][0];
    tape[1].push_back('_');
    for(int i=1; i < N; i++){
        tape[2*i].push_back('_');
        tape[2*i+1].push_back('_');
        syms[i]='_';
    }
    cur.old_states = state;
    cur.old_syms = syms;
    step = 0;
    bool brk = false;
    bool match = false;
    //第0步应该在外面打印
    printState();
    int cnt=0;
    int f=0;
    while(find(F.begin(), F.end(), cur.old_states)==F.end()){
        //终结状态集中找不到该state
        char tmp;
        brk = true;
        match=false;
        #ifdef DEBUG
        if(f<10){
            f++;
            cout << "f: " << f << " find: " << cur.old_states << " " << cur.old_syms << endl;
            // cout << "delta size " << delta.size() << endl;
        }
        #endif
        for(int i=0; i < delta.size(); i++){
            brk=false;

            if(delta[i].old_states==cur.old_states){
                for(int j=0; j < N; j++){//对比第i个
                    #ifdef DEBUG
                    if(f < 10){
                        cout << "cur: " << delta[i].old_states << " " << delta[i].old_syms << " " << delta[i].new_syms
                << " " << delta[i].new_dires << " " << delta[i].new_states << endl; 
                    }
                    #endif

                    if(delta[i].old_syms[j]!='*' && delta[i].old_syms[j]!=cur.old_syms[j] ||
                        delta[i].old_syms[j]=='*'&& cur.old_syms[j]=='_' ){//*和空格也不能匹配
                        // cout << '$' << endl;
                        brk = true;//不一样
                        break;
                    }
                }
                if(!brk){
                    //匹配成功
                    // cout << 55 << endl;
                //     if(cnt < 10){
                //         // cout << "match, before change state " << "cnt: "<< cnt <<  endl;
                //         // cout << cur.old_states << " " << cur.old_syms << endl;
                //         // cout << delta[i].old_states << " " << delta[i].old_syms << " " << delta[i].new_syms
                // // << " " << delta[i].new_dires << " " << delta[i].new_states << endl; 
                //         // printState();
                //         cnt++;
                //         }
                    // cout << "match" << endl;
                    cur.new_dires = delta[i].new_dires;
                    cur.new_states = delta[i].new_states;
                    cur.new_syms = delta[i].new_syms;
                    match = true;



                    step++;
                    //打印第step步

                    //更新old_syms
                    for(int j=0; j<N; j++){
                        // if(cnt<5)
                            // cout << "####syms: " << cur.new_syms[j] << '#'<<endl;
                        if(cur.old_syms[j]!=cur.new_syms[j] && cur.new_syms[j]!='*'){
                            cur.old_syms[j] = cur.new_syms[j];
                            // cout << "syms: " << cur.old_syms[j] << '#'<<endl;
                        }
                    }
                    //更新states
                    cur.old_states = cur.new_states;

                    //把old_syms写入纸带
                    for(int j=0; j < N; j++){
                        if(index[j]>=0) {
                            //index[j]>=0表示标号为正，tape为两条带中的第一条
                            tape[2*j][index[j]] = cur.old_syms[j];
                        }
                        else{
                            tape[2*j+1][-index[j]] = cur.old_syms[j];
                        }
                    }
                    // if(cnt<5)
                        // cout << "old_syms: " << cur.old_syms << endl;

                    //方向,移动读头
                    for(int j=0; j < N; j++){
                        if(cur.new_dires[j]=='r'){//第i个读头向右
                            if(index[j]>=0){
                                if(index[j]+1 + 1 > tape[2*j].size()){//index[j]的值从0开始，index[j]+1为对应纸带需要的size {
                                    tape[2*j].push_back('_');
                                }
                                // index[j]++;
                            }
                            // else {
                                //索引为﹣
                            index[j]++;
                            // }
                        }
                        else if(cur.new_dires[j]=='l'){
                            index[j]--;
                            if(index[j] < 0 && -index[j] + 1 > tape[2*j+1].size()){
                                tape[2*j+1].push_back('_');
                                // cout << "x " << index[j] <<  endl;
                            }
                        }
                    }
                    //更新cur.old_syms
                    for(int j = 0; j < N; j++){
                        if(index[j] >= 0)
                            cur.old_syms[j] = tape[2*j][index[j]];
                        else    
                            cur.old_syms[j] = tape[2*j+1][-index[j]];
                    }
                    printState();


                    // cout << '#' << endl;
                    break;
                }
                // else 
                //     brk = false;
            }
        }
        if(!match){
            #ifdef DEBUG
            cout << "no delta match!" <<  endl;
            #endif
            break;
        }
        // if(f<10){
        //     f++;
            // printState();
        // }
    }
    if(verbose){
        cout << "Result: ";
    }
    // if(!verbose){
        // cout << "1" << endl;
        int l=0, r=-1;
        if(tape[1].size()>1){
            for(int i = tape[1].size()-1; i > 0; i--){
                if(tape[1][i] != '_'){
                    l = -i;
                    break;
                }
            }
        }        
        if(l==0){
            for(int i = 0; i < tape[0].size(); i++){
                if(tape[0][i] != '_'){
                    l = i;
                    break;
                }
            }
        }
        for(int i = tape[0].size()-1; i >= 0; i--){
            if(tape[0][i]!='_'){
                r = i + 1;//右边界为开区间
                break;
            }
        }
        if(r==-1){
            //在左侧纸带寻找，从右往左找第一个不为空的字符
            for(int i = 1; i < tape[1].size(); i++){
                if(tape[1][i] != '_'){
                    r = -i + 1;
                    break;
                }
            }
        }
        // cout << l << " " << r << endl;
        for(int i = l; i < r; i++){
            if(i < 0){
                if(tape[1][-i]=='_')    
                    cout << " " ;
                else
                    cout << tape[1][-i];
            }
            else {//i > 0
                if(tape[0][i]=='_')    
                    cout << " " ;
                else
                    cout << tape[0][i];
            }
        }
        cout << endl;
    if(verbose){
        cout << "==================== END ====================" << endl;
    }
    // }
    // cout << "ends" << endl;

}
// template<typename T>
// bool TuringMachine::getVector(string str, vector<T> v, int kind){
//     //from 
// }
int main(int argc, char* argv[]){
    if(argc == 1){
        cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
        return 0;
    }
    else if(argc == 2){
        //-h ? -v ?
        if(!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")){
            cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
            return 0;
        }
        else {
            cerr << "Wrong Parameters!" << endl;
            exit(-1);
        }
    }
    else if(argc == 3){
        if(strcmp(argv[1], "-v")||strcmp(argv[1], "--verbose")){//not -v | --verbose
            TuringMachine* tm = new TuringMachine(argv[1], false);
            tm->resolver();
            tm->simulator(argv[2]);
            return 0;
        }
        else {
            cerr << "Wrong Parameters!" << endl;
            exit(-1);
        }
    }
    else if(argc == 4){
        if(!strcmp(argv[1], "-v") || !strcmp(argv[1], "--verbose")){
            TuringMachine* tm = new TuringMachine(argv[2], true);
            tm->resolver();
            tm->simulator(argv[3]);
            return 0;
        }
        else {
            cerr << "Wrong Parameters!" << endl;
            exit(-1);            
        }
    }
    else{
        cerr << "Wrong Parameters!" << endl;
        exit(-1);          
    }
    // return 0;
}