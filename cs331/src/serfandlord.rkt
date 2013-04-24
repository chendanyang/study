#lang racket
(define denizen-list null)

(struct denizen (master name class next-king next-freemen) #:transparent #:mutable)

(define king-sentinel
  (denizen null "King Sentinel the Great" 'lord null null))

(define (creat-lord name)
  (let ((nu-lord (denizen null name 'lord (denizen-next-king king-sentinel) null)))
    (set-denizen-next-king! king-sentinel (cons nu-lord (denizen-next-king king-sentinel)))
    (set! denizen-list (cons nu-lord denizen-list))))

(define (vaild a b)
  (or (equal b 'lord)
      (equal a 'serf)))

(define (serve a b)
(if (vaild (denizen-class a) (denizen-class b))  
  (set-denizen-master! a b)
  (error "You did something politicall correct in feudal times")))
