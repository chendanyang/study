#lang racket
(define (power x y)
  (cond [(= y 1) x]
        [else (* x (power x (- y 1)))]
        ))

(define (range x xx)
  (cond [(= x (* 2 xx)) null]
        [else (cons (- x xx) (range (+ x 1) xx))]
        ))

(define (append xx yy)
  (cond 