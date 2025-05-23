;; Hand class
(defpackage :hand
  (:use :cl :card))

(in-package :hand)

(defclass hand ()
  ((cards :initarg :cards :accessor hand-cards)
   (hand-type :initarg :hand-type :accessor hand-type)))

(defconstant +hand-size+ 5)

(defun make-hand ()
  (make-instance 'hand :cards '() :hand-type -1))

(defun add-card (hand card)
  (push card (hand-cards hand)))

(defun hand-to-string (hand)
  (mapconcat #'card-to-string (hand-cards hand) " "))

(defun get-sorted-cards (hand)
  (sort (copy-list (hand-cards hand)) #'compare-cards :key #'card-rank))

(defun set-hand-type (hand type)
  (setf (hand-type hand) type))

