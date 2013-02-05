#lang racket

(provide nim-tests)

(require rackunit)
(require "nim.rkt")

(define initial-moves (list->vector '(1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)))

(define nim-tests

  ; You will probably just have this one test suite

  (test-suite  "Tests for the Nim lab"

     ;;  But you will want more than one test-case
    (test-case "Does ai-computer-takes return 4?"
    (let  ((moves initial-moves))
      (check-pred (lambda (x) (< x 4)) (ai-computer-takes moves 21) 3) ))


    (test-case "Original computer-takes tests"
               (check-equal? 1 (computer-takes 1) "If only one stick, computer must take it.")
               (check-equal? 1 (computer-takes 2) "If two sticks, computer should take 1.")
               (check-equal? 2 (computer-takes 3) "If three sticks, computer should take 2."))

))

