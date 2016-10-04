;;Perceptrons 
(defparameter *outputs* '(1 1 -1 -1) )
(defparameter *weight* '(0 0 0 0) ) ;;w1 w2 w3 w4
(defparameter *b* 0 )
(defparameter *a* 0.09230213122301982308912380912083918092308912380921089 )
(defparameter *o* 0 )
(defparameter *input* '( (1 1 1 1) (-1 1 -1 -1) (1 1 1 -1 ) (1 -1 -1 1) ))

;;Check if the output is equal 
(defun check (lst)
  (let ( (result 0 ))
    (setf result (reduce #'+ (mapcar #'* lst *weight*)))
    (if (>= (+  *b* result) 0 )
	1
        -1)))
           
;;aux funcion for with-alpha 
(defun get-lst (lst output )
  (loop for item in lst
	collect
	(* *a* output item)))

;;Calculate the new weight 
(defun new-weight (lst &optional (output 1)) 
  (let  ((aux-lst (get-lst lst output)))
    (setf *weight* (mapcar #'+ *weight* aux-lst))
    (setf *b* (+ *b* (*  *a* output)))
    (list *weight* *b*)))

;;Train the algorithm (and count the times needed to get 100% accurated)
(defun train (&optional (count 0 ))
  (let ( (changed 0 )) 
    (loop for i below 4
	  do
	  (progn (if (equal (nth i *outputs* ) (check (nth i *input* )))
		     t
		   (progn (new-weight (nth i *input*) (nth i *outputs*))
			  (setf changed 1 ))) ))
    (if (equal changed 0 ) (format nil "Treinado com sucesso!~%Numero de iteracoes ~a" count )
        (train (+ 1 count ))) ))
       
(defun test (lst)
  (check lst )) 
