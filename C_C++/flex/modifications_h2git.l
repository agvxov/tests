/* @BAKE
    flex -o $*.yy.cpp $@ 
    g++ $*.yy.cpp -o modifications_h2git.out -ggdb
   @STOP
*/
%{
    #include <stdio.h>
    #include <string>
    #include <vector>

    using namespace std;

    typedef struct {
        string date;
        string msg;
    } commit_t;

    commit_t commit_buffer = (commit_t){
        .date = "N/A",
        .msg  = "N/A",
    };

    vector<commit_t> commits;
%}

%option noyywrap
%%

[0-9]+\/[0-9]+\/[0-9]{4} {
    if (commit_buffer.msg != "N/A") {
        commits.push_back(commit_buffer);
    }

    commit_buffer = (commit_t){
        .date = "",
        .msg  = "",
    };
    commit_buffer.date = yytext;
}

\t|\*|\r  { ; }

\n*    { commit_buffer.msg += ' '; }
\"     { commit_buffer.msg += "\\\""; }
.      { commit_buffer.msg += yytext; }

%%

signed main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("%s <modifications.h>", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    yylex();

    //for (auto i : commits) {
    //    printf("date: %s ; message: %s\n", i.date.c_str(), i.msg.c_str());
    //    puts("\033[31m-------\033[0m");
    //}

    // NOTE: https://unix.stackexchange.com/questions/3051/how-to-echo-a-bang
    puts("histchars='¡^'");

    for (auto i : commits) {
        printf("git commit --allow-empty --date='%s 00:00:00' -m \"%s\"\n",
                i.date.c_str(),
                i.msg.c_str()
            );
    }

    return 0;
}
