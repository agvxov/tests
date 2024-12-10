%{
    /* include/declaration of a buffer */
%}
%x IN_EXPORT IN_COMMENT IN_MULTILINE_COMMENT
%nodefault
%%
export  {
            BEGIN IN_EXPORT;
        }
\/\/    { BEGIN IN_COMMENT; }
\/\*    { BEGIN IN_MULTILINE_COMMENT; }
.|\n    { ; }

<IN_EXPORT>{
.           { /*appending*/ }
\n          { ; }
\;|\}|\=    {
                BEGIN INITIAL;
                /* store the buffer somewhere */
            }
}

<IN_COMMENT>{
.           { ; }
\n          { BEGIN INITIAL; }
}

<IN_MULTILINE_COMMENT>{
.|\n        { ; }
\*\/        { BEGIN INITIAL; }
}
%%

int yywrap() {
    yyin = /*XXX*/ NULL;
    return 0;
}
