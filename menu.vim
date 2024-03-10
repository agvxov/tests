"function! MyPopupCallback(selection)
"    if a:selection != -1
"        echo "Selected item: " . a:selection
"    else
"        echo "Menu closed without selection"
"    endif
"endfunction
"
""let s:menu_items = ['Item 1', 'Item 2', 'Item 3']
"
"" Bind the popup menu to F10
"noremap <F10> :call ShowPopupMenu()<CR>
"
"function! ShowPopupMenu()
"    let s:selected_item = popup_menu(['red', 'green'], #{
"                \ 'callback': 'MyPopupCallback',
"                \ })
"endfunction


noremap <F10> :call ShowPopup()<CR>

function! ShowPopup()
	call popup_atcursor(['red', 'green', 'blue'], #{} )
endfunction

autocmd TextChangedI * call ShowPopup()


"function! MyCompletionCallback(arg_lead, cmd_line, cursor_pos)
"    let candidates = ['Item 1', 'Item 2', 'Item 3']
"    return complete(col('.'), candidates)
"endfunction
"
"" Bind the completion menu to F10
"inoremap <F10> <C-o>:call ShowCompletionMenu()<CR>
"
"function! ShowCompletionMenu()
"    call complete(col('.'), ['j', 'b', 'k'] )
"endfunction

"inoremap <F10> <C-R>=ListMonths()<CR>
"
"func ListMonths()
"  call complete(col('.'), ['January', 'February', 'March',
"	\ 'April', 'May', 'June', 'July', 'August', 'September',
"	\ 'October', 'November', 'December'])
"  return ''
"endfunc
