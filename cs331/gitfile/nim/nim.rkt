#lang racket

(provide main run ai-computer-takes computer-takes)

;; Initial move chart
(define initial-moves (list->vector '(1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)))

(define (run)
  (read-line) ; to fix problem when running from emacs geiser-mode
  (main))

(define (main)
  (setup))

(define (computer-takes pile-size)
  (cond [(= pile-size 1) 1]
        [(<= pile-size 4) (- pile-size 1)]
        [else (+ 1 (random (min 3 pile-size)))]))


;; Your code needs to go in the ai-computer-takes function.
;; Computer should take 1,2, or 3 sticks each turn.
;; Have the computer take as many sticks as possible, if it won't lose.
;; If there is no way to win, the computer needs to mark the current element as "losing".
;; If the computer is sure to lose, it will take 3 to get it over with.

(define (ai-computer-takes moves pile-size)
  ;  (min pile-size 3) ; this is reasonable
  4 ; this is an error.  The test case will spot it.
  )

(define (person-takes moves pile)
  (printf "There are ~a pieces.  How many will you take? " pile)
  (define taken (read))
  (cond [(not (integer? taken))
         (begin (printf "Please enter an integer!~n")
                (person-takes moves pile))]

        [(> taken pile)
         (begin (printf "There aren't that many pieces left.~n")
                (person-takes moves pile))]
        
        [(or (> taken 3) (< taken 1))
         (begin (printf "You must take 1,2,or 3 pieces.~n")
                (person-takes moves pile))]
        
        [else taken]))

(define (check-winner who pile)
  (if (equal? pile 0)
      (begin
        (printf "~a took the last piece.  ~a lost.~n" who who)
        #t)
      #f))

(define (save-ai fname moves)
  (with-output-to-file fname
    (lambda () (write (vector->list moves))) #:exists 'replace))

(define (load-ai fname)
  (with-handlers [(exn?
                   (lambda (e) initial-moves))]
    (with-input-from-file fname
      (lambda () (list->vector (read))))))

(define (game players moves pile)
  (let ((remaining-sticks (play-a-round players moves pile)))
    (if (equal? remaining-sticks 0)
        (begin 
          (printf "Game over.~n") 
          (printf "Saving AI.~n")
          (save-ai "nim-moves.rkt" moves)
          (read-line) ; get rid of LF
          (if (equal? (ask "Play again? ") "y")
              (game players moves 21)
              (printf "See ya!~n")))
        (game players moves remaining-sticks))))


(define (play-a-round players moves pile)
  (if (null? players) pile
      (let ((takes ( (if (equal? (cdar players) "c") ; ask the professor to explain this in class!
                         ai-computer-takes
                         person-takes)
                     moves pile )))
        (printf "~a takes ~a.~n" (caar players) takes)
        (define nu-pile (- pile takes))
        (if (check-winner (caar players) nu-pile)
            0 ; we're done.  You will not need to modify this.
            (play-a-round (cdr players) moves nu-pile)))))

(define (ask question)
  (printf question)
  (read-line)
  )

(define (setup)
  (let [(players
         (list (cons (ask "What is the name of the human player? ") "h")
               (cons "The Computer" "c")))
        (moves (load-ai "nim-moves.rkt"))]
    (game players moves 21)))


                             
;; For standalone running
;; type:
;;   racket nim.rkt

(module* main #f (main))


