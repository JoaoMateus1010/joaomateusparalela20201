all:	
	git add .
	git commit -m '\$(COMMIT)$\'
	git push --force
status:
	git status