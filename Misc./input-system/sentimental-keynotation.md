# Sentimental hotkey notation

> Standard to describe the key combination notation used by Sentimental LLC

## Context

A combination of keys being pressed to invoke a single action is referred to as a hotkey.

There are numerous dialects of hotkey notations, this is ours.

This document is in the Public Domain.

## Grammar

```bnf
hotkey : space keys
       ;

keys : key
     | key addition keys
     ;

addition : + space
         ;

space : %empty
      | ' ' space
      ;

key : key space
    | a-z
    | 0-9
    | `-=[]\;',./
    | function
    | mouse
    | modifier
    | special
    ;

function : f(1-12)
         ;

mouse : m(1-9)
      ;

modifier : ctrl
         | shift
         | alt
         | win
         ;

special : tab
        | enter
        | caps
        | up
        | down
        | left
        | right
        ;
```

Statements over 63 characters may not be accepted by parsers.

In the future it is possible sequences hotkeys will be added,
 which can only be read by state machines.
If so, the character `&` shall be used as a new operator between keys.

## Examples

**Valid** examples:
* `a` (simple)
* `ctrl+a` (combination)
* `ctrl+lalt+t` (multiple combination)
* `t+lalt+ctrl` (order does not matter)
* `ctrl + a` (space around +)
* ` ctrl+a  ` (space around keys)
* `a + a` (behaves as `a`; tho implementations are recommended to warn)

**Invalid** examples:
* ` ` (empty)
* `a+` (unterminated)
* `Ctrl+a` (upper case not allowed)
* `lctrl+a` (lctrl or rctrl is not a key, only ctrl is)

## Notes

> [!NOTE]
> Everything is always lower case to avoid confusion.
> E.g. this would be ambiguous if we used title case: `Alt + N`.

> [!NOTE]
> Just because the grammar allows a key combination,
> it does not mean its biddable by our implementation(s).
> For example "q+e" is valid and would be commonly referred to as a chord,
>  but games rarely allow it.

> [!NOTE]
> No Emil, the Autohotkey notation is NOT reasonable;
>  its a spreadsheet game for autistic people.

> [!NOTE]
> The order of keys and modifiers is not specified to ease parsing.
> Only a psycho would use `t+alt+ctrl` in practice,
>  but its better if we just don't know.
