#lang racket
(struct dlist (front back size) #:mutable)
(struct dnode (prev data next) #:mutable)
(define (make-dlist) (dlist null null 0))
(define (inc-dlist-size! dlist)
  (set-dlist-size! dlist (+ 1 (dlist-size dlist))))
(define (inset-front dlist elt)
  (let ((node (dnode null elt (dlist-front dlist))))
    (cond ((null? (dlist-front dlist))
           (begin (set-dlist-front! dlist node)
                  (set-dlist-back! dlist node)
                  (inc-dlist-size! dlist)))
          (else (begin (set-dnode-prev! (dlist-front dlist) node)
                       (set-dlist-front! dlist node)
                       (inc-dlist-size! dlist))))
    ))
