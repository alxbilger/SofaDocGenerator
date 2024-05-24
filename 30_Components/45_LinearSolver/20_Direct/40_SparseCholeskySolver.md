This component belongs to the category of [LinearSolver](https://www.sofa-framework.org/community/doc/main-principles/system-resolution/linear-solvers/). The role of the SparseLUSolver is to solve the linear system <img class="latex" src="https://latex.codecogs.com/png.latex?\mathbf{A}x=b" title="Linear system" /> assuming that the matrix <img class="latex" src="https://latex.codecogs.com/png.latex?\mathbf{A}" title="System matrix" /> is symmetric and sparse.

The Cholesky decomposition (https://en.wikipedia.org/wiki/Cholesky_decomposition) is a numerical method that solves a linear system <img class="latex" src="https://latex.codecogs.com/png.latex?\mathbf{A}x=b" title="Linear system" /> by factorizing the matrix of the system as <img class="latex" src="https://latex.codecogs.com/png.latex?\mathbf{LL^T}" title="Linear system" />. By doing so, we only need to solve two triangular systems to compute the solution. It is only applyable on **symetric** matrices but is roughtly twice as efficient as the LU solver. The <img class="latex" src="https://latex.codecogs.com/png.latex?\mathbf{LDL^T}" /> decomposition is heavily related to the Cholesky decomposition.

<div align="center">
<img class="latex" src="https://latex.codecogs.com/png.latex?\begin{cases}
\mathbf{A}x=b \\
\mathbf{A}=\mathbf{LL^T}
\end{cases}
\Longleftrightarrow 
\begin{cases}
 \mathbf{L} y = b \\
 \mathbf{L}^T x = y \\
 \end{cases}"
title="Linear systems" />

<div align="Left">

Sequence diagram
----------------

<a href="https://github.com/sofa-framework/doc/blob/master/images/linearsolver/SparseCholeskySolver.png?raw=true"><img src="https://github.com/sofa-framework/doc/blob/master/images/linearsolver/SparseCholeskySolver.png?raw=true" title="Flow diagram for the SparseCholeskySolver"/></a>

The SparseCholeskySolver **requires** the use (above in the scene graph) of an integration scheme, and (below in the scene graph) of a MechanicalObject storing the state information that the SparseCholeskySolver will access.


Data  
----
There is one data that change the behaviour of the solver, **permutation**, that allows three choices :
**-None**, no permutation, nor on the rows nor on the columns, is applied
**-SuiteSparse**, use the SuiteSparse library as intended for a symmetric matrix and apply a fill reducing permutation on both the columns and the rows (those two permutations are the inverse of each other),
**-METIS**, use the METIS library to compute a fill reducing permutation and apply it on both the lines and the columns.

It is not currently possible to change the type of permutation applied during a simulation.

Applying a fill reducing permutation aims at minimizing the number of non-null values in the decomposition, which would reduce the time spent on solving the triangular systems.

As the impact of the use of fill reducing permutations on the performances is highly influenced by the repartition of the nodes used to model an object, we advise the users to test which type of permutation is the best suited for their simulations.


Example
-------

This component is used as follows in XML format:

``` xml
<SparseCholeskySolver  />
```

or using SofaPython3:

``` python
node.addObject('SparseCholeskySolver')
```

An example scene involving a SparseCholzskySolver is available in [*applications/plugins/CSparseSolvers/examples/FEMBAR_SparseCholeskySolver.scn*](https://github.com/sofa-framework/sofa/blob/master/applications/plugins/CSparseSolvers/examples/FEMBAR_SparseCholeskySolver.scn)
<!-- automatically generated doc START -->
__Target__: Sofa.Component.LinearSolver.Direct

__namespace__: sofa::component::linearsolver::direct

__parents__: 
- MatrixLinearSolver

Data: 

<table>
<thead>
    <tr>
        <th>Name</th>
        <th>Description</th>
        <th>Default value</th>
    </tr>
</thead>
<tbody>
	<tr>
		<td>name</td>
		<td>
object name
</td>
		<td>unnamed</td>
	</tr>
	<tr>
		<td>printLog</td>
		<td>
if true, emits extra messages at runtime.
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>tags</td>
		<td>
list of the subsets the objet belongs to
</td>
		<td></td>
	</tr>
	<tr>
		<td>bbox</td>
		<td>
this object bounding box
</td>
		<td></td>
	</tr>
	<tr>
		<td>componentState</td>
		<td>
The state of the component among (Dirty, Valid, Undefined, Loading, Invalid).
</td>
		<td>Undefined</td>
	</tr>
	<tr>
		<td>listening</td>
		<td>
if true, handle the events, otherwise ignore the events
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>parallelInverseProduct</td>
		<td>
Parallelize the computation of the product J*M^{-1}*J^T where M is the matrix of the linear system and J is any matrix with compatible dimensions
</td>
		<td>0</td>
	</tr>

</tbody>
</table>

Links: 

| Name | Description |
| ---- | ----------- |
|context|Graph Node containing this object (or BaseContext::getDefault() if no graph is used)|
|slaves|Sub-objects used internally by this object|
|master|nullptr for regular objects, or master object for which this object is one sub-objects|
|linearSystem|The linear system to solve|




<!-- automatically generated doc END -->
