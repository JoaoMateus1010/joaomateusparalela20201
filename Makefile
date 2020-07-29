all:	
	git add .
	git commit -m '\$(COMMIT_MSG)$\'	

status:
	git status

push:
	git push --force

pull:
	git pull --rebase