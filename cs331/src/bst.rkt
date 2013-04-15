#lang racket
(struct queue (array [front #:mutable] [back #:mutable]))
(define (make-queue) (queue (make-vector 10) 0 0))
(define (enqueue q elt)
  (vector-set! (queue-array q) (queue-back q) elt)
  (set-queue-back! q (modulo (+ (queue-back q) 1)
                             (vector-length (queue-array q)))))
(define (dequeue q)
  (let ((top (vector-ref (queue-array q) (queue-front q))))
    (set-queue-front! q (modulo (+ (queue-front q) 1)
                                (vector-length (queue-array q))))
     top))
(define (top q)
  (vector-ref (queue-array q) ( queue-front q)))
;;(require "queue-class.rkt")by hand

(define-struct bst (data left right) #:transparent)

;;adding element
(define (add elt tree)
  (cond [(null? tree) (bst elt '() '())]
        [(< elt (bst-data tree))
         (bst (bst-data tree) (add elt (bst-left tree)) (bst-right tree))]
        [(> elt (bst-data tree))
         (bst (bst-data tree) (bst-left tree) (add elt (bst-right tree)))]
        [else tree]
        ))
;;mulit-add
(define (mulit-add tree elts)
  (if (null? elts) tree
      ;;else
      (mulit-add (add (car elts) tree) (cdr elts))))
;;find predecessor
(define (go-right tree)
  (if (null? (bst-right tree)) tree
      ;;else
      (go-right (bst-right tree))))
;;what is this used for?
(define (find-pred tree)
  (go-right (bst-left tree)))

;;search patterns1 depth first
(define (dfs tree elt)
  (and (not (null? tree))
       (or (equal? (bst-data tree) elt)
           (dfs (bst-left tree) elt)
           (dfs (bst-right tree) elt))))

;;search patterns2 breadth first
(define (bfs tree elt);;outface
  (define queue (make-queue))
  (enqueue queue tree)
  (bfs-aux queue elt)
  )
(define a (mulit-add null '(4 2 6 1 3 5 9)))

(define (bfs-aux queue elt);;inface
  (if (empty? queue) #f
      (let ([candidate (dequeue queue)])
        ;;candidate is a complete tree node contains bst-data bst-left...
        (or (equal? (bst-data candidate elt))
            (begin (unless (null? (bst-left candidate))
                           (enqueue queue (bst-left candidate)))
                   (unless (null? (bst-right candidate))
                           (enqueue queue (bst-right candidate)))
                   (bfs queue elt))))))
      
;;traversal1 preorder
(define (preorder tree)
  (if (null? tree) null
      (begin 
       (printf "Visiting ~a~%" (bst-data tree))
       (preorder (bst-left tree))
       (preorder (bst-right tree))
       )))
;;traversal2 postorder
(define (postorder tree)
  (if (null? tree) null
      (begin
        (postorder (bst-left tree))
        (postorder (bst-right tree))
        (printf "Visiting ~a~%" (bst-data tree)))))
;;traversal3 inorder
(define (inorder tree)
  (if (null? tree) '()
      (begin
        (inorder (bst-left tree))
        (printf "Visiting ~a~%" (bst-data tree))
        (inorder (bst-right tree))
        )))
