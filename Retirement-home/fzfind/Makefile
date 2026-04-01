help:
	@env echo -e "Available targets:\n\tinstall\n\tuninstall\n\tclean\n\ttest\n\tproduction"

test:
	gcc last_word.c -o last_word -g

production:
	gcc last_word.c -o lastWord -O3

install: production
	sudo cp lastWord /usr/bin

uninstall:
	sudo rm /usr/bin/lastWord

clean:
	rm out/*
