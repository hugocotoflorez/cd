all:
	gcc cd.c -Wall -o cd -g

git:
	git add .
	git commit -m "update src"
	git push
