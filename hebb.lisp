(defparameter *parameter-lst* nil)
(defparameter *weight* nil) 
(defparameter *linear* 0 )


(defun gen-parameter (n)
  (loop for x below n
	do
	(push (gensym) *parameter-lst*)))



(defun get-b (train-data)
  (let ( (b 0 ))
    (loop for data-level in train-data
	  do
	  (setf b (+ b (car (last data-level))) ))
    b))
	

(defun get-weight (train-data n)
  (gen-parameter n)
  (let ( (weight (make-list  n :initial-element 0)))
    (loop for data-level in train-data
	  do
	    (loop for i below (- n 1)
		  do
		  (setf (nth i weight) (+ (nth i weight) (* (nth i data-level)
							    (nth (- n 1) data-level))) )))
    (setf *weight* weight)
    (setf (car (last *weight*)) (get-b train-data)))
  *weight*)

(defun net (lst  n )
  (let ( (class (car (last *weight*)) ))
    (loop for i below n 
	  do
	    (setf class (+ class (* (nth i lst)
				    (nth i *weight*)) )))
	  class))


(defun train (data input-size)
  (setf *weight* nil)
  (if (get-weight data input-size) (format nil "Sucessfull trained")
    (format nil "Erro training")))


(defun run (input-lst)
  (let ( (n (1- (length *weight*)) ))
    (if (>= (net input-lst n) *linear*)
	1
      0
      )))
      
  
	  
