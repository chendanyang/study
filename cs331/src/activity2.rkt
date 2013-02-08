#lang racket
(define (power x y)
  (cond [(= y 1) x]
        [else (* x (power x (- y 1)))]
        ))

(define (range1 x xx)
  (cond [(= x (* 2 xx)) null]
        [else (cons (- x xx) (range1 (+ x 1) xx))]
        ))

(define (range2 x)
  (range-aux 0 x))
  
(define (range-aux i x)
  (if (< i x) 
      (cons i (range-aux (+ i 1) x))
            '()))
   
(define (myappend xx yy)
  (cond [(null? xx) (cond [(null? yy) null]
                          [else (myappend yy null)])]
        [else (cons (car xx) (myappend (cdr xx) yy))]
        ))
        
(define aa '(1 23 4 5))
(define bb '(2 3 4 5))

(define (bad-reverse xx)
  (if (null? xx) '()
      (append (bad-reverse (car xx)) (list (car xx))))
  )

(define (my-reverse-aux xx acc)
  (if (null? xx) acc
      (my-reverse-aux (cdr xx) (cons (car xx) acc))))

(define (my-reverse xx)
  (my-reverse-aux xx '()))