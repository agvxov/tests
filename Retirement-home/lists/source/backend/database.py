import sqlite3

class connection(sqlite3.Connection):
	database_file = 'data.sqlite3'
	def __init__(self):
		super().__init__(self.database_file)
		self.row_factory = sqlite3.Row
