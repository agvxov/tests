main:
	@echo "available targets: clean batch_commit"

clean:
	-rm *.out

batch_commit:
	@for file in $(shell git ls-files --others --exclude-standard); do \
	  git add $$file; \
	  git commit -m "Added '$$file'"; \
	done
