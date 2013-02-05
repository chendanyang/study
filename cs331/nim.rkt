#lang racket

(define (run)
  (read-line) ; for chewing up emacs buffer
  (main))

(define (main)
  (game (setup) 21))

(define (computer-takes pile)
  (cond [(= pile 1) 1]
        [(<= pile 4) (- pile 1)]
        [else (+ 1 (random (min 3 pile)))]))

(define (person-takes pile)
  (printf "There are ~a pieces.  How many will you take? " pile)
  (define taken (read))
  (cond [(not (integer? taken))
         (begin (printf "Please enter an integer!~n")
                (person-takes pile))]

        [(> taken pile)
         (begin (printf "There aren't that many pieces left.~n")
                (person-takes pile))]
        
        [(or (> taken 3) (< taken 1))
         (begin (printf "You must take 1,2,or 3 pieces.~n")
                (person-takes pile))]
        
        [else taken]))

(define (check-winner who pile)
  (if (equal? pile 0)
      (begin
        (printf "~a took the last piece.  ~a lost.~n" who who)
        #t)
      #f))


(define (game players pile)
  (let ((remaining-sticks (play-a-round players pile)))
    (if (equal? remaining-sticks 0)
        (printf "Game over.~n") 
        (game players remaining-sticks)))
)


(define (play-a-round players pile)
  (cond [ (null? players) pile]
        [ (equal? (cdar players) "c")
          (define c-m (computer-takes pile))
          (printf "~s takes ~s.~n" (caar players) c-m)
          (define pile-1 (- pile c-m))
          (if (check-winner (caar players) pile-1)
              0 ; we're done
              (play-a-round (cdr players) pile-1))]
        [ (equal? (cdar players) "h")
          (define p-m (person-takes pile))
          (printf "~s takes ~s.~n" (caar players) p-m)
          (define pile-2 (- pile p-m))
          (if (check-winner (caar players) pile-2)
              0 ; we're done
              (play-a-round (cdr players) pile-2))]))



(define (ask question)
  (printf question)
  (read-line)
)

(define (setup)
  (define name (ask "What is the name of the next player? (enter to stop) "))
  (if (equal? name "") '()
      (cons (cons name (ask "(c)omputer or (h)uman? ")) (setup) )))
