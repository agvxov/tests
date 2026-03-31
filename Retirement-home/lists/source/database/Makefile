init:
	sqlite3 data.sqlite3 < init.sql

seed_test:
	sqlite3 data.sqlite3 < dummy_seed.sql

test: init seed_test
	# pass
