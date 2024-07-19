syn region A start="region_A{" end="}" transparent
syn keyword myKeyword keyword_a contained containedin=A

syn region AB start="region_AB{" end="}" transparent
syn keyword myKeyword keyword_ab contained containedin=AB

hi link myKeyword Statement
