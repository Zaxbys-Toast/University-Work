;; Hand Identifier class
(defpackage :hand-identifier
  (:use :cl :hand))

(in-package :hand-identifier)

(defclass hand-identifier () ())

(defmethod assign-type ((class hand-identifier) hand)
  (let ((cards (get-sorted-cards hand)))
    (cond
      ((royal-straight-flush-p cards) (set-hand-type hand 9))
      ((straight-flush-p cards) (set-hand-type hand 8))
      ((four-of-a-kind-p cards) (set-hand-type hand 7))
      ((full-house-p cards) (set-hand-type hand 6))
      ((flush-p cards) (set-hand-type hand 5))
      ((straight-p cards) (set-hand-type hand 4))
      ((three-of-a-kind-p cards) (set-hand-type hand 3))
      ((two-pair-p cards) (set-hand-type hand 2))
      ((pair-p cards) (set-hand-type hand 1))
      (t (set-hand-type hand 0)))))

(defun royal-straight-flush-p (cards) (and (straight-p cards) (flush-p cards)))

(defun straight-flush-p (cards) (and (straight-p cards) (flush-p cards)))

(defun four-of-a-kind-p (cards) (let ((freq (card-frequency cards))) (some #'(lambda (x) (= x 4)) freq)))

(defun full-house-p (cards) (let ((freq (card-frequency cards))) (and (member 3 freq) (member 2 freq))))

(defun flush-p (cards) (let ((suit (card-suit (first cards)))) (every #'(lambda (c) (= (card-suit c) suit)) cards)))

(defun straight-p (cards) (let ((ranks (mapcar #'card-rank cards)))
                            (loop for i from 0 to (1- (length ranks)) do
                                  (if (not (= (elt ranks i) (+ (elt ranks 0) i))) (return nil)))
                            t))

(defun two-pair-p (cards) (let ((freq (card-frequency cards))) (member 2 freq)))

(defun pair-p (cards) (let ((freq (card-frequency cards))) (member 2 freq)))

(defun card-frequency (cards)
  (let ((freq (make-hash-table)))
    (dolist (card cards)
      (incf (gethash (card-rank card) freq 0)))
    (hash-table-values freq)))

