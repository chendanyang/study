#lang racket
(define size 0)
(define (merge x1 x2)
  (merge-aux x1 x2 0 0 size)
  
  )

(define (merge-aux x1 x2 point1 point2 size)
  (cond [(null? x1) (cond [(null? x2) null]
                          [else (cons (car x2) (merge-aux null (cdr x2) point1 (+ point2 1) (+ size 1)))])]
        [(null? x2) (cond [(null? x1) null]
                          [else (cons (car x1) (merge-aux (cdr x1) null (+ point1 1) point2 (+ size 1)))])]
        [(>= (car x1) (car x2)) (cons (car x2) (merge-aux x1 (cdr x2) point1 (+ point2 1) (+ size 1)))]
        [(< (car x1) (car x2)) (cons (car x1) (merge-aux (cdr x1) x2 (+ point1 1) point2 (+ size 1)))]
       ;; [else  (cons (car x2) (merge-aux x1 (cdr x2) point1 (+ point2 1) (+ size 1)))]
        ))
