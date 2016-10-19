#Neural Logic
* Hebb Algorithm and Perceptrons implemented for Robotic Class.  
* This was writted in Common Lisp.
* Created by Lucas Guerra.
* Contact lu.guerra7508@gmail.com .


#How to use

<h4> HEBB </h4> 
```lisp
  (load "hebb.lisp")
  (train '( (-1 -1 -1) (-1 1 -1) (1 -1 -1) (1 1 1)) 3)	
```
<p> How this work
<p> Train get a list, this list represent the true table of the circuit
<p> -1 means 0 and 1 means 1
<p> The next function input is the size of each list
<p> That means, all the inputs + output (0 0 1) -> 3
* The weight resulted by the algorithm can be acessed calling the variable *weight*
```lisp
(run '(-1 -1)) ;; Will run the algorithm after the training of the neural network.
```
<h4> Perceptron </h4>
```lisp
  (load "perceptron")
  (train)
  (check '(1 1 1 1))
```
<p> This algorithm was a simple perceptron with only 4 weight.
<p> Just a sample of how to implement a perceptron in Common Lisp.


#Details


<h4> Hebb </h4> 
* Can be passed list with N number of inputs
* The algorithm is just a Hebb Algorithm implementation, soo, will not be precise as it should be.
<h4> Perceptrons </h4>
*Is just a sample of perceptrons impremented in Common Lisp .
<p> 
* Any doubt or bugs you can send me a email. 
