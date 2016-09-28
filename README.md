#Neural Logic
* Hebb Algorithm for Neural Networks and Logical Circuits.
* This was writted in Common Lisp.
* Created by Lucas Guerra.
* Contact lu.guerra7508@gmail.com .


#How to use

* (load "hebb.lisp")
* (train '( (-1 -1 -1) (-1 1 -1) (1 -1 -1) (1 1 1)) 3)	
<p> How this work
<p> Train get a list, this list represent the True table of the circuit
<p> -1 means 0 and 1 means 1
<p> The next funcion input is the size of each list
<p> That means, all the inputs + output (0 0 1) -> 3
* The weigth resulted by the algorithm can be acessed calling the variable *weigth*
* (run '(-1 -1))-> Will run the algorithm after the trainnig of the neural network.


#Details

* Can be passed list with N number of inputs
* The algorithm is just a Hebb Algorithm implementation, soo, will not be precise as it should be.
*Any doubt or bugs you can send me a email. 