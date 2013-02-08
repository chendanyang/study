#lang racket
(define (power x y)
  (cond [(= y 1) x]
        [else (* x (power x (- y 1)))]
        ))

(define (range x xx)
  (cond [(= x (* 2 xx)) null]
        [else (cons (- x xx) (range (+ x 1) xx))]
        ))

(define (myappend xx yy)
  (cond [(null? xx) (cond [(null? yy) null]
                          [else (myappend yy null)])]
        [else (cons (car xx) (myappend (cdr xx) yy))]
        ))
        
(define aa '(1 23 4 5))
(define bb '(2 3 4 5))

(define (reverse xx)
  (conds [(null? xx) null]
         [