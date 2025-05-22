(defun find-len (i &optional (count 0))
  (if (= i 1)
      count
      (find-len (if (evenp i)
                    (/ i 2)
                    (+ (* i 3) 1))
                (+ count 1))))

(defun process-range (min-range max-range)
  (if (>= min-range max-range)
      (progn
        (princ "minRange must be less than maxRange")
        (return-from process-range)))
  
  (let ((lengths '())  ; List to hold the lengths
        (index-lengths '()))  ; List to hold the corresponding indexes
    (loop for i from min-range to (1- max-range) do
      (let ((j (find-len i)))
        (if (< (length lengths) 10)
            (progn
              (push j lengths)  ; Add the sequence length to the list
              (push i index-lengths))  ; Add the corresponding index to the list
            (when (> j (apply 'min lengths))
              (let ((min-index (position (apply 'min lengths) lengths :test #'=)))
                (setf (nth min-index lengths) j)
                (setf (nth min-index index-lengths) i))))))
    
    ;; Sorting by sequence length in descending order
    (let* ((sorted-pairs (sort (mapcar #'list lengths index-lengths)
                               #'> :key #'first))
           (sorted-lengths (mapcar #'first sorted-pairs))
           (sorted-indexes (mapcar #'second sorted-pairs)))
      (princ "Sorted based on sequence length:")
      (terpri)
      (loop for length in sorted-lengths
            for index in sorted-indexes do
            (format t "~d ~d~%" index length))
      
      ;; Sorting by integer size (index) in descending order
      (let* ((sorted-by-index (sort (mapcar #'list lengths index-lengths)
                                    #'> :key #'second))
             (sorted-lengths-by-index (mapcar #'first sorted-by-index))
             (sorted-indexes-by-index (mapcar #'second sorted-by-index)))
        (terpri)
        (princ "Sorted based on integer size:")
        (terpri)
        (loop for length in sorted-lengths-by-index
              for index in sorted-indexes-by-index do
              (format t "~d ~d~%" index length))))))

(if (/= (length sb-ext:*posix-argv*) 3)
    (princ "Must Include a Range. Example: sbcl --script collatz.lisp 1 100")
    (let ((min-range (parse-integer (nth 1 sb-ext:*posix-argv*) :junk-allowed t))
          (max-range (parse-integer (nth 2 sb-ext:*posix-argv*) :junk-allowed t)))
      (if (or (not min-range) (not max-range) (>= min-range max-range))
          (princ "Invalid range. Ensure minRange is less than maxRange and both are integers.")
          (process-range min-range max-range))))
(terpri)

