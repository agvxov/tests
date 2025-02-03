#!/bin/bash

RED='\033[1;31m'
RESET='\033[0m'

## Coreutils
#CMDS=(
#    basename
#    cat
#    chgrp
#    chmod
#    chown
#    chroot
#    cp
#    cut
#    date
#    dd
#    df
#    dir
#    dirname
#    du
#    echo
#    env
#    expr
#    false
#    head
#    ln
#    ls
#    mkdir
#    mkfifo
#    mknod
#    mktemp
#    mv
#    pwd
#    readlink
#    rm
#    rmdir
#    seq
#    sleep
#    sort
#    stty
#    sync
#    tail
#    touch
#    tr
#    true
#    tty
#    uname
#    vdir
#    wc
#    yes
#    arch
#    b2sum
#    base32
#    base64
#    basename
#    basenc
#    chcon
#    chroot
#    cksum
#    comm
#    csplit
#    cut
#    dir
#    dircolors
#    dirname
#    du
#    env
#    expand
#    expr
#    factor
#    fmt
#    fold
#    head
#    hostid
#    id
#    install
#    join
#    link
#    logname
#    md5sum
#    mkfifo
#    mktemp
#    nice
#    nl
#    nohup
#    nproc
#    numfmt
#    od
#    paste
#    pathchk
#    pinky
#    pr
#    printenv
#    printf
#    ptx
#    readlink
#    realpath
#    runcon
#    seq
#    sha1sum
#    sha224sum
#    sha256sum
#    sha384sum
#    sha512sum
#    shred
#    shuf
#    sleep
#    sort
#    split
#    stat
#    stdbuf
#    sum
#    tac
#    tail
#    tee
#    test
#    timeout
#    touch
#    tr
#    truncate
#    tsort
#    tty
#    uname
#    unexpand
#    uniq
#    unlink
#    users
#    vdir
#    wc
#    who
#    whoami
#    yes
#)

# Moreutils
CMDS=(
    chronic
    combine
    errno
    ifdata
    ifne
    isutf8
    lckdo
    mispipe
    moreutils_parallel
    pee
    sponge
    ts
    vidir
    vipe
    zrun
)

for cmd in "${CMDS[@]}"; do
    if ! command -v "$cmd" &>/dev/null; then
        echo "Skipping missing command: $cmd"
        continue
    fi

    for flag in "--help" "-h"; do
        echo "Running: $cmd $flag"
        $cmd $flag </dev/null &>/dev/null
        EXIT_CODE=$?

        if [ $EXIT_CODE -ne 0 ]; then
            echo -e "${RED}ERROR: $cmd $flag failed with exit code $EXIT_CODE${RESET}"
        fi
    done
done
