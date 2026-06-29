syn keyword Loops while for do foreach

sy region String start="'" end="'"
sy region Shell start="\${" end="}" oneline

    syntax case match

synt match Instruction "^\s*#inst"
"synt match Instruction "^\s*#inst"

hi link Loops       mybold
hi link String      mybold
hi link Shell       mybold
hi link Instruction mybold

hi mybold term=bold cterm=bold ctermfg=darkBlue
