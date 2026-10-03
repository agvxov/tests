# mktemplate
This script attempts to eliminate user overhead of frequently coping a file to varying locations.
Mktemplate internally attempts to read a variable called "${MKTEMPLATE_HOME}".
This variable shall hold the path to the folder where templates are stored.
"Templates" are just files located at ${MKTEMPLATEHOME}.
Text files are processed through m4.

---

I used to use this to restore my imageboard filters after firefox crashes.
It mixes snippet and dotfile management with templating in a way that sorta-kinda makes sense.
It used to be helpful, but never really comfortable,
especially because I did not have `histui` back in the day.
