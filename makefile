all:
	gcc cd.c -Wall

git:
	git add .
	git commit -m "update src"
	git push
