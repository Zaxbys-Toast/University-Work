(defpackage :deck
  (:use :cl :card))

(in-package :deck)

(defclass deck ()
  ((cards :initarg :cards :accessor deck-cards)))
(defparameter +rank-map+ '("2" "3" "4" "5" "6" "7" "8" "9" "10" "J" "Q" "K" "A"))
(defparameter +suit-map+ '("H" "D" "C" "S"))
(defun make-deck ()
  (let ((cards (loop for rank in +rank-map+
                    append (loop for suit in +suit-map+
                                 collect (make-card rank suit)))))
    (setf cards (shuffle-list cards))
    (make-instance 'deck :cards cards)))

(defun shuffle-list (list)
  (loop with shuffled = list
        do (rotatef (nth (random (length list)) shuffled) (nth (random (length list)) shuffled))
        finally (return shuffled)))

(defun deal-card (deck)
  (pop (deck-cards deck)))

(defun print-deck (deck)
  (loop for card in (deck-cards deck) do
        (format t "~A " (card-to-string card))
        when (zerop (mod (position card (deck-cards deck) :test 'eq) 13)) do (terpri)))
