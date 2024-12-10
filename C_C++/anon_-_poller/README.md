// ### Poller spec ###
 + take repeated input from stdin
 + consider each terminated input line a command
 + valid commands
    - poll <question>; (<max_voting>)
    - poll_status
    - vote [n|y]
 + the program only needs to keep track of 1 poll
 + every vote is boolean
 + <max_voting> is optional
 + if more then half of <max_voting> number of people agreed, echo that the question is decided and what the verdict is 
