#lang racket
(define (delete-all xx elt)
   (cond [(null? xx) null ]
         [(equal? (car xx) elt) (delete-all (cdr xx) elt)]
         [else (cons (car xx) (delete-all (cdr xx) elt))]
         ))

(define a '(1 2 3 4 5 3 6 3))

(define (flatten xx)
  (cond [(null? xx) null]
        [(list? (car xx)) (flatten (append (car xx) (cdr xx)))]
        [else (cons (car xx) (flatten (cdr xx)))]
        ))

(define (flat xx)
  (cond [(null? xx) null]
        [(list? (car xx)) (append (car xx) (flat (cdr xx)))]
        ))

(define aa '((1 23 3) (1 2322) () (5)))