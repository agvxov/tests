main: .peru/lastimports

.peru/lastimports: peru.yaml .peru
	source venv/bin/activate; \
	peru sync

.peru: venv
	source venv/bin/activate; \
	pip install peru

venv:
	python -m venv venv

clean:
	-source venv/bin/activate; \
	pip install peru; \
	deactivate
	-rm -frfr venv/
	-rm -frfr .peru/
