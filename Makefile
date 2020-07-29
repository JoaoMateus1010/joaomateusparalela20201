all:	
	git add .
	git commit -m '\$(COMMIT)$\'	

status:
	git status

push:
	git push --force
	
pull:
	git pull --rebase