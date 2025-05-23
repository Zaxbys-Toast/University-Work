(defpackage :main
  (:use :cl :card :deck :hand :hand-identifier :hand-sorter))

(in-package :main)

(defun main ()
  (let* ((deck (make-deck))                            ; Create and shuffle a new deck
         (hands (loop repeat 6 collect (make-hand))))  ; Create 6 empty hands

    ;; Deal cards in a round-robin manner
    (dotimes (i +hand-size+)
      (dolist (hand hands)
        (add-card hand (deal-card deck))))

    ;; Assign hand types using the hand-identifier class
    (let ((identifier (make-instance 'hand-identifier)))
      (dolist (hand hands)
        (assign-type identifier hand)))

    ;; Sort the hands by type and resolve ties
    (let ((sorter (make-instance 'hand-sorter)))
      (sort-hands sorter hands))

    ;; Print out sorted hands and their types
    (loop for hand in hands
          do (format t "Hand: ~A~%Type: ~A~%"
                     (hand-to-string hand)
                     (hand-type hand)))))
(main)
