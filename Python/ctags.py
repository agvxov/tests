import ctags
from ctags import CTags, TagEntry

tagFile = CTags('tags')

entry = TagEntry()
status = tagFile.first(entry)

print(entry[b'scope'])
