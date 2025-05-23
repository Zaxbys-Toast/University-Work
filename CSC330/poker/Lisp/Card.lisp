(defpackage :card
  (:use :cl))

(in-package :card)

;; Ranks and Suits Mapping
(defconstant +rank-map+ '("2" "3" "4" "5" "6" "7" "8" "9" "10" "J" "Q" "K" "A"))
(defconstant +suit-map+ '("D" "C" "H" "S"))

;; Card class
(defclass card ()
  ((rank :initarg :rank :accessor card-rank)
   (suit :initarg :suit :accessor card-suit)))

(defun make-card (rank suit)
  (let ((rank-index (position rank +rank-map+ :test 'string=))
        (suit-index (position suit +suit-map+ :test 'string=)))
    (if (and rank-index suit-index)
        (make-instance 'card :rank (+ rank-index 1) :suit (+ suit-index 1))
        (error "Invalid card rank or suit"))))

(defun card-to-string (card)
  (format nil "~A~A"
          (elt +rank-map+ (- (card-rank card) 1))
          (elt +suit-map+ (- (card-suit card) 1))))

(defun compare-cards (card1 card2)
  (cond
    ((< (card-rank card1) (card-rank card2)) -1)
    ((> (card-rank card1) (card-rank card2)) 1)
    (t (if (< (card-suit card1) (card-suit card2)) -1 1))))
