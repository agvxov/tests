%{
    #include <string>
    #include <dictate.hpp>

    const char * input_str;
    int len;
    int offset;
    #define YY_INPUT(buf, result, max_size) {                        \
        int cpi = (offset && offset > max_size) ? max_size : offset; \
        memcpy(buf, input_str+(len-offset), cpi);                    \
        result = cpi;                                                \
        offset = (cpi > offset) ? 0 : offset - cpi;                  \
    }

    using namespace std;

    string r;
%}

%s IN_STRING IN_BLOB IN_PATTERN

    /* Reverse ESCape */
resc    \||\(|\)

%option noyywrap nodefault
%option prefix="regex"
%%
    BEGIN INITIAL;

<INITIAL>{
\"          {
                BEGIN IN_STRING;
            }
\'          {
                BEGIN IN_BLOB;
            }
\/          {
                BEGIN IN_PATTERN;
            }
.           {
                dictate("Not a literal.\n");
                return 0;
            }
}

<IN_STRING>{
\\(<|>)     {
                r += "\\b";
            }
\\{resc}    {
                r += yytext + 1;
            }
{resc}      {
                r += "\\";
                r += yytext;
            }
.           {
                r += yytext;
            }
}

<IN_BLOB>{
\\          {
                r += "\\\\";
            }
.           {
                r += yytext;
            }
}

<IN_PATTERN>{
.           {
                r += yytext;
            }
}

\n          { /*NOTREACHED*/; }

%%

string vim2pcre(const char * pattern) {
    extern string r;
    r = "";

    input_str = pattern;
    len       = strlen(pattern);
    offset    = len;

    regexlex();

    r = r.substr(0, r.size()-1);

    return r;
}
