%option noyywrap
%x COMMENT
%%
<INITIAL>\/\*    { BEGIN COMMENT; }
<COMMENT>{
.    { ; }
\*\/ { BEGIN INITIAL; }
}
%%
