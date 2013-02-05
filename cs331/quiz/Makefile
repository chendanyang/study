SITE=http://dijkstra.cs.iit.edu/cs331/static/linux-lab

quiz:
	rm -rf quizdir quiz.tgz
	wget ${SITE}/quiz.tgz
	tar xzf quiz.tgz

clean:
	rm -rf quizdir
	rm -f quiz.tgz

submit:
	@ls -laR quizdir | mutt -a solutions.txt -- beckman@iit.edu
	@echo Thanks for submitting your quiz.  The instructor will look at
	@echo the results and let you know the results.  Please do not
	@echo run Make submit again unless you need to change something.
