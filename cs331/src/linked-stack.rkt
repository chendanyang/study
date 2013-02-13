#lang racket
;;--------linked-stack------------------
(struct stack (list) #:mutable)
(define (make-stack) (stack null))
(define (push s elt)
  (set-stack-list! s(cons elt (stack-list s) )))
(define (pop s)
  (let ((top (car (stack-list s))))
    (set-stack-list! s (cdr (stack-list s) ))
     top))
(define (top s)
  (car (stack-list s)))