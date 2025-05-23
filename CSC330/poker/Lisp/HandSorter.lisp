;; Hand Sorter class
(defpackage :hand-sorter
  (:use :cl :hand))

(in-package :hand-sorter)

(defclass hand-sorter () ())

(defmethod sort-hands ((class hand-sorter) hands)
  (sort-hands-by-type hands)
  (sort-ties hands))

(defun sort-hands-by-type (hands)
  (setf hands (sort hands #'(lambda (a b) (> (hand-type b) (hand-type a))))))

(defun sort-ties (hands)
  (dolist (hand hands)
    (let ((same-type-hands (remove-if-not #'(lambda (h) (= (hand-type h) (hand-type hand))) hands)))
      (setf same-type-hands (sort same-type-hands #'(lambda (a b) (> (card-rank (first a)) (card-rank (first b)))))))))
