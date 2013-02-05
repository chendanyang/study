#lang racket

(define-struct arraylist (v cursor) #:mutable)


(define (insert al elt)
  (when (>= (arraylist-cursor al) (vector-length (arraylist-v al)))
      (let ((nu-vec (make-vector (* 2 (vector-length (arraylist-v al))))))
        (for ((i (in-range (vector-length (arraylist-v al))))) 
          (vector-set! nu-vec i (vector-ref (arraylist-v al) i)))
        (set-arraylist-v! al nu-vec)))
  (vector-set! (arraylist-v al) (arraylist-cursor al) elt)
  (set-arraylist-cursor! al (+ (arraylist-cursor al) 1)))
