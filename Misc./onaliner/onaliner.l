/*
    @BAKE
        flex -o $*.yy.c $@
        gcc $*.yy.c -o onaliner -lfl
    @STOP
*/
%{
    #define ECHOC(c) fputc(c, yyout)
%}

%option nodefault
%x ALLMAN_BRACE_SCAN PAREN_ONALINE

ws			[ \t\r\v\f]

%%
\(  {
        ECHO;
        BEGIN PAREN_ONALINE;
    }
.   {
        ECHO;
    }
\n  {
        BEGIN ALLMAN_BRACE_SCAN;
    }

<ALLMAN_BRACE_SCAN>{
^{ws}*\{    {
                ECHOC('{');
                BEGIN INITIAL;
            }
.|\n        {
                ECHOC('\n');
                yyless(0);
                BEGIN INITIAL;
            }
}
<PAREN_ONALINE>{
\)  {
        /* NOTE:
            this obviously breaks literals, for example:
                myfunction(')');
            However, since the point of this program to clean up definitions,
             that would only matter if
                1) the function head has default values
                2) the default value contains ')'
                3) the function head is multilined
            For example:
                void cpp_be_damned(const char * lol = "(lmao even)",
                                    int get_fucked = 1
                );
            This seems like such a special case that it seems unrealistic to prepare for,
             in the context of not wanting to make assumptions of the input language
             other than its roughly C like.
            Because if we were to prepare for it, might as well prepare for JS's
             `string literal` syntax and so on and so on...
        */
        ECHO;
        BEGIN INITIAL;
    }
.   {
        ECHO;
    }
\n  { ; }
}
%%
