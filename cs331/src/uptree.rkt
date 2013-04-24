#lang racket
(struct up-tree (parent data) #:transparent #:mutable)
(define (add elt)
  (let ((me (up-tree '() elt)))
    (begin
      (set-up-tree parent! me me)
      me)))
;without path compression

(define (find node)
  (if (eq? (up-tree-parent node) node) node
      (find (up-tree-parent node))))

(define (union a b)
  (set-up-tree-parent! (find a) (find b)))

;withpath compression
(define (find-path node)
  (if (eq? (up-tree-parent node) node) node
      (let ((rep (find-path (up-tree-parent node))))
	(begin
	  (set-up-tree-parent! node rep)
	  rep))))
(define (union-path a b)
  (set-up-tree-parent! (find-path a) (find-path b)))
