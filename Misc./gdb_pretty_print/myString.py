class myStringPrinter:
	def __init__(self, val):
		self.val = val
	def to_string(self):
		return str(self.val['a'])

def mylookup(val):
	if str(val.type) == 'myString':
		return myStringPrinter(val)
	return None

gdb.pretty_printers.append(mylookup)
