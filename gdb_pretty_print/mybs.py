class mybsPrinter:
	def __init__(self, val):
		self.val = val
	def to_string(self):
		s = ""
		char_ptr = gdb.lookup_type("char").pointer()
		char_ptr_ptr = char_ptr.pointer()
		v = self.val['v']
		for i in range(0, v['element_count']):
			s += (
					str(
						(
							v['data'].cast(char_ptr_ptr)
								+
							i
						).dereference()
					)
							+
						", "
				)
		return s

def mylookup(val):
	if str(val.type) == 'mybs':
		return mybsPrinter(val)
	return None

gdb.pretty_printers.append(mylookup)
