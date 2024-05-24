# ShewchukPCGLinearSolver

Linear system solver using the conjugate gradient iterative algorithm


__Templates__:
- GraphScattered

__Target__: Sofa.Component.LinearSolver.Iterative

__namespace__: sofa::component::linearsolver::iterative

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
	<tr>
		<td>iterations</td>
		<td>
maximum number of iterations of the Conjugate Gradient solution
</td>
		<td>25</td>
	</tr>
	<tr>
		<td>tolerance</td>
		<td>
desired precision of the Conjugate Gradient Solution (ratio of current residual norm over initial residual norm)
</td>
		<td>1e-05</td>
	</tr>
	<tr>
		<td>use_precond</td>
		<td>
Use preconditioner
</td>
		<td>1</td>
	</tr>
	<tr>
		<td>update_step</td>
		<td>
Number of steps before the next refresh of precondtioners
</td>
		<td>1</td>
	</tr>
	<tr>
		<td>build_precond</td>
		<td>
Build the preconditioners, if false build the preconditioner only at the initial step
</td>
		<td>1</td>
	</tr>
	<tr>
		<td>graph</td>
		<td>
Graph of residuals at each iteration
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
|linearSystem|The linear system to solve|
|preconditioner|Link towards the linear solver used to precondition the conjugate gradient|



<!-- automatically generated doc START -->
__Target__: Sofa.Component.LinearSolver.Iterative

__namespace__: sofa::component::linearsolver::iterative

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
	<tr>
		<td>iterations</td>
		<td>
Maximum number of iterations of the Conjugate Gradient solution
</td>
		<td>25</td>
	</tr>
	<tr>
		<td>tolerance</td>
		<td>
Desired accuracy of the Conjugate Gradient solution evaluating: |r|²/|b|² (ratio of current residual norm over initial residual norm)
</td>
		<td>1e-05</td>
	</tr>
	<tr>
		<td>threshold</td>
		<td>
Minimum value of the denominator (pT A p)^ in the conjugate Gradient solution
</td>
		<td>1e-05</td>
	</tr>
	<tr>
		<td>warmStart</td>
		<td>
Use previous solution as initial solution
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>graph</td>
		<td>
Graph of residuals at each iteration
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
|linearSystem|The linear system to solve|



## Examples

```xml
<?xml version="1.0"?>
<Node name="root" dt="0.02" gravity="0 -10 0">
    <RequiredPlugin name="Sofa.Component.Constraint.Projective"/> <!-- Needed to use components [FixedProjectiveConstraint] -->
    <RequiredPlugin name="Sofa.Component.LinearSolver.Iterative"/> <!-- Needed to use components [CGLinearSolver] -->
    <RequiredPlugin name="Sofa.Component.Mass"/> <!-- Needed to use components [UniformMass] -->
    <RequiredPlugin name="Sofa.Component.ODESolver.Backward"/> <!-- Needed to use components [EulerImplicitSolver] -->
    <RequiredPlugin name="Sofa.Component.SolidMechanics.FEM.Elastic"/> <!-- Needed to use components [HexahedronFEMForceField] -->
    <RequiredPlugin name="Sofa.Component.StateContainer"/> <!-- Needed to use components [MechanicalObject] -->
    <RequiredPlugin name="Sofa.Component.Topology.Container.Grid"/> <!-- Needed to use components [RegularGridTopology] -->
    <RequiredPlugin name="Sofa.Component.Visual"/> <!-- Needed to use components [VisualStyle] -->
    <VisualStyle displayFlags="showBehaviorModels showForceFields" />
    <DefaultAnimationLoop/>
    
    <Node>
        <EulerImplicitSolver name="eulerimplicit_odesolver" printLog="false"  rayleighStiffness="0.1" rayleighMass="0.1" />
        <CGLinearSolver iterations="100" tolerance="1e-20" threshold="1e-20" warmStart="1" />
        <MechanicalObject />
        <UniformMass vertexMass="1" />
        <RegularGridTopology nx="4" ny="4" nz="4" xmin="-9" xmax="-6" ymin="0" ymax="3" zmin="0" zmax="3" />
        <FixedProjectiveConstraint indices="0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15" />
        <HexahedronFEMForceField name="FEM" youngModulus="4000" poissonRatio="0.3" method="large" />
    </Node>
</Node>
```
```python
def createScene(rootNode):

	root = rootNode.addChild('root', dt="0.02", gravity="0 -10 0")
	root.addObject('RequiredPlugin', name="Sofa.Component.Constraint.Projective")
	root.addObject('RequiredPlugin', name="Sofa.Component.LinearSolver.Iterative")
	root.addObject('RequiredPlugin', name="Sofa.Component.Mass")
	root.addObject('RequiredPlugin', name="Sofa.Component.ODESolver.Backward")
	root.addObject('RequiredPlugin', name="Sofa.Component.SolidMechanics.FEM.Elastic")
	root.addObject('RequiredPlugin', name="Sofa.Component.StateContainer")
	root.addObject('RequiredPlugin', name="Sofa.Component.Topology.Container.Grid")
	root.addObject('RequiredPlugin', name="Sofa.Component.Visual")
	root.addObject('VisualStyle', displayFlags="showBehaviorModels showForceFields")
	root.addObject('DefaultAnimationLoop')

	root = root.addChild('root')
	root.addObject('EulerImplicitSolver', name="eulerimplicit_odesolver", printLog="false", rayleighStiffness="0.1", rayleighMass="0.1")
	root.addObject('CGLinearSolver', iterations="100", tolerance="1e-20", threshold="1e-20", warmStart="1")
	root.addObject('MechanicalObject')
	root.addObject('UniformMass', vertexMass="1")
	root.addObject('RegularGridTopology', nx="4", ny="4", nz="4", xmin="-9", xmax="-6", ymin="0", ymax="3", zmin="0", zmax="3")
	root.addObject('FixedProjectiveConstraint', indices="0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15")
	root.addObject('HexahedronFEMForceField', name="FEM", youngModulus="4000", poissonRatio="0.3", method="large")
```

<!-- automatically generated doc END -->
