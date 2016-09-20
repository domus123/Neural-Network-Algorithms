(defparameter *parameter-lst* nil)
(defparameter *weigth* nil) 
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
	

(defun get-weigth (train-data n)
  (gen-parameter n)
  (let ( (weigth (make-list  n :initial-element 0)))
    (loop for data-level in train-data
	  do
	    (loop for i below (- n 1)
		  do
		  (setf (nth i weigth) (+ (nth i weigth) (* (nth i data-level)
							    (nth (- n 1) data-level))) )))
    (setf *weigth* weigth)
    (setf (car (last *weigth*)) (get-b train-data)))
  *weigth*)

(defun net (lst  n )
  (let ( (class (car (last *weigth*)) ))
    (loop for i below n 
	  do
	    (setf class (+ class (* (nth i lst)
				    (nth i *weigth*)) )))
	  class))


(defun train (data input-size)
  (setf *weigth* nil)
  (if (get-weigth data input-size) (format nil "Dados treinados com sucesso")
    (format nil "Erro ao treinar dados")))


(defun run (input-lst)
  (let ( (n (1- (length *weigth*)) ))
    (if (>= (net input-lst n) *linear*)
	1
      0
      )))
      
  
	  
