set instructions {
    {syscall}
    {sysret}
    {sysexit}
    {sysenter}
    {leave}
    {retf}
    {retn}
    {pause}
    {hlt}
    {lock}
}

    # {mov register immediate}
    
proc malformed_instruction {i} {
    error [format "Instruction {%s} is malformed" [join $i ", "]]
}
