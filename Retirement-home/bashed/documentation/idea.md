> bash is the least bad shell out there.

# What do i call a bash ditribution
+ a package which contains either a custom build of bash or
   custom configurations out of the box

# Bash distributions in the wild
+ oh-my-bash
    - the documentation is **terrible**
    - fucks up by trying to maintain its own completion
    - provides an interface to manage plugins
    - allows for styling
+ bash-it
    - the documentation is **terrible**
    - literally 0 internet coverage despine over GH 14k starts
    - provides an interface to manage plugins
    - allows for styling

# Why i think this is a good idea
+ the competition is weak, solid documentation and a few articles and videos,
   and the accessibility war is won
+ stock bash is terrible
+ bash is a pain to configure because there are 6 gorrion minor things that has to be changed
   either by hand or by deep diving into abandonware
+ there is no interactive bashtutor (think `vimtutor`) to stock or for distros,
   the closest thing i found is this: [bash-tutor](https://github.com/Sitwon/bash-tutor)
   which has the right idea, but is very basic abandonware,
   ideally if you download a pack of non-standard commands configurations
   you would like something like this to get you familiar

# What i think it should look like
+ reasonable readline settings
+ "repo" of preconfigured prompts
+ easy way to enable/disable features (lets not call them plugins,
   because thats associated with gays and AIDS);
   the way i think it should go is that the user sources a file from their
   .bashrc, this contains all modifications and individual ones can be
   toggled using variables, similar to C feature macros
+ [cd-rc](https://github.com/agvxov/cd_rc)
+ kali ls aliases {l, ll, ls='+a'}
+ [bash-completion](https://github.com/scop/bash-completion)
+ [ls-colors](https://github.com/trapd00r/LS_COLORS) (btw the owner of this project is an absolute nigger)
+ (optional) login ascii art (i really like that when changing to Root)
+ human friendly aliasing of common inhumane (READ: "GNU") utilities
+ having a turor for both basic bash (to lure in newfags) and the distro
+ recursive aliases
+ highlighting
    - now, as far as i know this should be possible with just bash, its just that no one bothered;
       one could theoretically bind every key to run through a wrapper which inserts ascii sequences
       to the line being edited, then strip them uppon enter; however i suspect the performance would
       be ALMOST as terrible as typing in Microcock Visual Studio
    - forking and adding a wrapper function to GNU readline which does basically what is described ABOVE
       should be only mildy painful; on stackoverflow ive read talks about such wizardry except
       coonfiger NEETs seem to have a serious problem with contributing to the FOSS ecosystem
+ histui integration if i ever get to fucking make it
