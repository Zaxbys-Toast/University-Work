#!/usr2/local/sbcl/bin/sbcl --script

;;; Define a name to be used as a variable
(defvar A)

;;; Set up the variable to hold a 5x5 matrix
(setf A (make-array '(5 5)))

;;; Start the process of filling the matrix
(dotimes (i 5)
  (dotimes (j 5)
	;;; Watch carefully, the next line is creating a LIST and putting the
	;;; LIST in each array element so each array element will contain
	;;; something like
	;;; 2 x 2 = 4
	;;; Also notice the PREFIX notation (* i j).  This is common in LISP
	;;; programming when using operators and predicates.
	(setf (aref A i j) (list i 'x j '= (* i j)))
	)
  )

;;; Now print out the whole thing
(dotimes (i 5)
  (dotimes (j 5)
	(print (aref A i j))
	)
  )
(terpri)

