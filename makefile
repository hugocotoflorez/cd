all:
	gcc cd.c -Wall -o cd

git:
	git add .
	git commit -m "update src"
	git push
