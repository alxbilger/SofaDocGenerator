---
title: FixedProjectiveConstraint
---

FixedProjectiveConstraint
===============

This component belongs to the category of [Projective Constraint](https://www.sofa-framework.org/community/doc/main-principles/constraint/projective-constraint/). The FixedProjectiveConstraint projects a constant velocity. If the fixed points have a zero velocity at the simulation start, they will keep a zero velocity i.e. be fixed.

As introduced in the page about the Projective Constraint, the FixedProjectiveConstraint corresponds to a projection matrix noted <img class="latex" src="https://latex.codecogs.com/png.latex?\mathbf{P}" title="Projection matrix" /> which will multiply the system matrix <img class="latex" src="https://latex.codecogs.com/png.latex?\mathbf{A}" title="System matrix" /> so that: <img class="latex" src="https://latex.codecogs.com/png.latex?\mathbf{P}^T\mathbf{A}\mathbf{P}%20\Delta%20v=\mathbf{P}^Tb" title="Constrained system" />. This projection matrix <img class="latex" src="https://latex.codecogs.com/png.latex?\mathbf{P}" title="Projection matrix" /> is the identity matrix in which the diagonal value corresponding to the indices of the fixed points equals zero. These lines and columns equals 0. As a consequence, when the integration scheme (ODESolver) will call the ```projectResponse()``` or ```projectVelocity()``` the constraint will be applied, ensuring that the desired degrees of freedom remain fixed.

Example of a system of size 6, with a fixed constraint at the indice 5:
<center>
<img class="latex" src="https://latex.codecogs.com/png.latex?%5Cmathbf%7BP%7D%20%3D%20%5Cbegin%7Bbmatrix%7D%201%20%26%200%20%26%200%20%26%200%20%26%200%20%26%200%20%5C%5C%200%20%26%201%20%26%200%20%26%200%20%26%200%20%26%200%20%5C%5C%200%20%26%200%20%26%201%20%26%200%20%26%200%20%26%200%20%5C%5C%200%20%26%200%20%26%200%20%26%201%20%26%200%20%26%200%20%5C%5C%200%20%26%200%20%26%200%20%26%200%20%26%20%5Cmathbf%7B0%7D%20%26%200%20%5C%5C%200%20%26%200%20%26%200%20%26%200%20%26%200%20%26%201%20%5Cend%7Bbmatrix%7D" title="Projection matrix" />
</center>

By projecting this <img class="latex" src="https://latex.codecogs.com/png.latex?\mathbf{P}" title="Projection matrix" /> matrix on the right hand side vector we have <img class="latex" src="https://latex.codecogs.com/png.latex?\mathbf{P}^Tb" title="Constrained system" />. This ensures to have the projection <img class="latex" src="https://latex.codecogs.com/png.latex?b[5]=0" title="Fixed 5th point" />, thus preventing any time evolution of the fifth degree of freedom. In such case, we function _projectResponse()_:

```cpp
template <class DataTypes>
void FixedProjectiveConstraint<DataTypes>::projectResponse(const core::MechanicalParams* mparams, DataVecDeriv& resData)
{
    SOFA_UNUSED(mparams);

    helper::WriteAccessor<DataVecDeriv> res (resData );
    const SetIndexArray & indices = d_indices.getValue();

    if( d_fixAll.getValue() )
    {
        // fix everything
        typename VecDeriv::iterator it;
        for( it = res.begin(); it != res.end(); ++it )
        {
            *it = Deriv();
        }
    }
    else
    {
        for (SetIndexArray::const_iterator it = indices.begin(); it != indices.end(); ++it)
        {
            res[*it] = Deriv();
        }
    }
}
```


Data 
----

The FixedProjectiveConstraint can be initialized using three input data:

- **indices**: corresponding to the indices of the fixed points
- **fixAll**: filters all the DOF to implement a fixed object
- **activate_projectVelocity**: if true, projects not only a constant but a zero velocity



Usage
-----

The FixedProjectiveConstraint **requires** a MechanicalObject to store the degrees of freedom associated to the nodes, as well as a Mass so that the system matrix is not null. An integration scheme and a solver are also necessary to solve the linear system at each time step.

Note that if only a part of the degrees of freedom must be constraint, you can use the PartialFixedProjectiveConstraint working in the same way as the FixedProjectiveConstraint.



Example
-------

This component is used as follows in XML format:

``` xml
<FixedProjectiveConstraint name="FixedProjectiveConstraint" indices="3 39 64" />
```

or using SofaPython3:

``` python
node.addObject('FixedProjectiveConstraint', indices='3 39 64')
```

An example scene involving a FixedProjectiveConstraint is available in [*examples/Component/Constraint/Projective/FixedProjectiveConstraint.scn*](https://github.com/sofa-framework/sofa/blob/master/examples/Component/Constraint/Projective/FixedProjectiveConstraint.scn)
<!-- automatically generated doc START -->
__Target__: `Sofa.Component.Constraint.Projective`

__namespace__: `#!c++ sofa::component::constraint::projective`

__parents__: 

- `#!c++ ProjectiveConstraintSet`

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
		<td>group</td>
		<td>
ID of the group containing this constraint. This ID is used to specify which constraints are solved by which solver, by specifying in each solver which groups of constraints it should handle.
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>endTime</td>
		<td>
The constraint stops acting after the given value.
Use a negative value for infinite constraints
</td>
		<td>-1</td>
	</tr>
	<tr>
		<td>indices</td>
		<td>
Indices of the fixed points
</td>
		<td></td>
	</tr>
	<tr>
		<td>fixAll</td>
		<td>
filter all the DOF to implement a fixed object
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>activate_projectVelocity</td>
		<td>
activate project velocity to set velocity
</td>
		<td>0</td>
	</tr>
	<tr>
		<td colspan="3">Visualization</td>
	</tr>
	<tr>
		<td>showObject</td>
		<td>
draw or not the fixed constraints
</td>
		<td>1</td>
	</tr>
	<tr>
		<td>drawSize</td>
		<td>
0 -&gt; point based rendering, &gt;0 -&gt; radius of spheres
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
|mechanicalStates|List of mechanical states to which this component is associated|
|mstate|MechanicalState used by this component|
|topology|link to the topology container|




<!-- automatically generated doc END -->
