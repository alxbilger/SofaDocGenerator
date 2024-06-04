---
title: AttachProjectiveConstraint
---

AttachProjectiveConstraint
================

This component belongs to the category of [Projective Constraint](https://www.sofa-framework.org/community/doc/main-principles/constraint/projective-constraint/). The AttachProjectiveConstraint works with a pair of objects and it projects the degrees of freedom (e.g. position) and their derivatives (e.g. velocity), so that both objects are attached. As being a projective constraint, this projective constraints ensures a geometrical connection between both objects at the end of the time step but it does not integrate the physics of both object (contrary to Lagrange based constraints).



Data 
----

The AttachProjectiveConstraint can be initialized using three input data:

- **object1**: link to the first model (MechanicalModel)
- **object2**: link to the second model (MechanicalModel)
- **indices1**: corresponding to the indices of the source points on the first model
- **indices2**: corresponding to the indices of the fixed points on the second model
- **constraintFactor**: allows for the partial application of the constraint using this factor per pair of points constrained (0=the constraint is released. 1=the constraint is fully constrained)
- **twoWay**:
  - if true, this boolean projects the constraint vertices of both _object1_ and _object2_ towards their average degrees of freedom and derivatives: 
  ```cpp
  Deriv corr = (dx2-dx1)*0.5*responseFactor*getConstraintFactor(index);
        dx1 += corr;
        dx2 -= corr;
  ```
  - if false, the position of the _object1_ are projected onto the _object2_. Therefore, _object2_ only follows _object1_ without affecting the motion of _object1_
  ```cpp
  dx2 = Deriv();
  ```



Usage
-----

The AttachProjectiveConstraint **requires** two MechanicalObjects so that both degrees of freedom can be accessed and projected to the attached configuration. An integration scheme and a solver are also necessary to solve the linear system at each time step.


Example
-------

This component is used as follows in XML format:

``` xml
<AttachProjectiveConstraint name="AttachProjectiveConstraint" object1="@M1" object2="@M2" indices1="0 1 2" indices2="10 11 12" constraintFactor="1 1 1"/>
```

or using SofaPython3:

``` python
node.addObject('AttachProjectiveConstraint', object1="@M1", object2="@M2", indices1="0 1 2", indices2="10 11 12", constraintFactor="1 1 1")
```

An example scene involving a AttachProjectiveConstraint is available in [*examples/Component/Constraint/Projective/AttachProjectiveConstraint.scn*](https://github.com/sofa-framework/sofa/blob/master/examples/Component/Constraint/Projective/AttachProjectiveConstraint.scn)
<!-- automatically generated doc START -->
__Target__: `Sofa.Component.Constraint.Projective`

__namespace__: `#!c++ sofa::component::constraint::projective`

__parents__: 

- `#!c++ PairInteractionProjectiveConstraintSet`

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
		<td>indices1</td>
		<td>
Indices of the source points on the first model
</td>
		<td></td>
	</tr>
	<tr>
		<td>indices2</td>
		<td>
Indices of the fixed points on the second model
</td>
		<td></td>
	</tr>
	<tr>
		<td>twoWay</td>
		<td>
true if forces should be projected back from model2 to model1
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>freeRotations</td>
		<td>
true to keep rotations free (only used for Rigid DOFs)
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>lastFreeRotation</td>
		<td>
true to keep rotation of the last attached point free (only used for Rigid DOFs)
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>restRotations</td>
		<td>
true to use rest rotations local offsets (only used for Rigid DOFs)
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>lastPos</td>
		<td>
position at which the attach constraint should become inactive
</td>
		<td></td>
	</tr>
	<tr>
		<td>lastDir</td>
		<td>
direction from lastPos at which the attach coustraint should become inactive
</td>
		<td></td>
	</tr>
	<tr>
		<td>clamp</td>
		<td>
true to clamp particles at lastPos instead of freeing them.
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>minDistance</td>
		<td>
the constraint become inactive if the distance between the points attached is bigger than minDistance.
</td>
		<td>-1</td>
	</tr>
	<tr>
		<td>positionFactor</td>
		<td>
IN: Factor applied to projection of position
</td>
		<td>1</td>
	</tr>
	<tr>
		<td>velocityFactor</td>
		<td>
IN: Factor applied to projection of velocity
</td>
		<td>1</td>
	</tr>
	<tr>
		<td>responseFactor</td>
		<td>
IN: Factor applied to projection of force/acceleration
</td>
		<td>1</td>
	</tr>
	<tr>
		<td>constraintFactor</td>
		<td>
Constraint factor per pair of points constrained. 0 -&gt; the constraint is released. 1 -&gt; the constraint is fully constrained
</td>
		<td></td>
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
|object1|First object associated to this component|
|object2|Second object associated to this component|




<!-- automatically generated doc END -->
