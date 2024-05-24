# InteractionEllipsoidForceField

Repulsion applied by an ellipsoid toward the exterior or the interior


__Templates__:
- Vec3d,Rigid3d

__Target__: Sofa.Component.MechanicalLoad

__namespace__: sofa::component::mechanicalload

__parents__: 
- MixedInteractionForceField

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
		<td>isCompliance</td>
		<td>
Consider the component as a compliance, else as a stiffness
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>rayleighStiffness</td>
		<td>
Rayleigh damping - stiffness matrix coefficient
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>contacts</td>
		<td>
Contacts
</td>
		<td></td>
	</tr>
	<tr>
		<td>center</td>
		<td>
ellipsoid center
</td>
		<td></td>
	</tr>
	<tr>
		<td>vradius</td>
		<td>
ellipsoid radius
</td>
		<td></td>
	</tr>
	<tr>
		<td>stiffness</td>
		<td>
force stiffness (positive to repulse outward, negative inward)
</td>
		<td>500</td>
	</tr>
	<tr>
		<td>damping</td>
		<td>
force damping
</td>
		<td>5</td>
	</tr>
	<tr>
		<td>color</td>
		<td>
ellipsoid color. (default=[0.0,0.5,1.0,1.0])
</td>
		<td>0 0.5 1 1</td>
	</tr>
	<tr>
		<td>object2_dof_index</td>
		<td>
Dof index of object 2 where the forcefield is attached
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>object2_forces</td>
		<td>
enable/disable propagation of forces to object 2
</td>
		<td>1</td>
	</tr>
	<tr>
		<td>object2_invert</td>
		<td>
inverse transform from object 2 (use when object 1 is in local coordinates within a frame defined by object 2)
</td>
		<td>0</td>
	</tr>
	<tr>
		<td colspan="3">Visualization</td>
	</tr>
	<tr>
		<td>draw</td>
		<td>
enable/disable drawing of the ellipsoid
</td>
		<td>1</td>
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



## Examples

```xml
<!-- Mechanical InteractionEllipsoidForceField Example -->
<Node name="root" gravity="0.0 -2.0 0.0" dt="0.04">
    <RequiredPlugin name="Sofa.Component.Collision.Detection.Algorithm"/> <!-- Needed to use components [BVHNarrowPhase BruteForceBroadPhase CollisionPipeline] -->
    <RequiredPlugin name="Sofa.Component.Collision.Detection.Intersection"/> <!-- Needed to use components [NewProximityIntersection] -->
    <RequiredPlugin name="Sofa.Component.Collision.Response.Contact"/> <!-- Needed to use components [CollisionResponse] -->
    <RequiredPlugin name="Sofa.Component.Constraint.Projective"/> <!-- Needed to use components [FixedProjectiveConstraint PartialFixedProjectiveConstraint] -->
    <RequiredPlugin name="Sofa.Component.Engine.Select"/> <!-- Needed to use components [BoxROI] -->
    <RequiredPlugin name="Sofa.Component.LinearSolver.Iterative"/> <!-- Needed to use components [CGLinearSolver] -->
    <RequiredPlugin name="Sofa.Component.Mapping.Linear"/> <!-- Needed to use components [IdentityMapping] -->
    <RequiredPlugin name="Sofa.Component.Mass"/> <!-- Needed to use components [UniformMass] -->
    <RequiredPlugin name="Sofa.Component.MechanicalLoad"/> <!-- Needed to use components [InteractionEllipsoidForceField] -->
    <RequiredPlugin name="Sofa.Component.ODESolver.Backward"/> <!-- Needed to use components [EulerImplicitSolver] -->
    <RequiredPlugin name="Sofa.Component.ODESolver.Forward"/> <!-- Needed to use components [EulerExplicitSolver] -->
    <RequiredPlugin name="Sofa.Component.SolidMechanics.Spring"/> <!-- Needed to use components [MeshSpringForceField QuadBendingSprings] -->
    <RequiredPlugin name="Sofa.Component.StateContainer"/> <!-- Needed to use components [MechanicalObject] -->
    <RequiredPlugin name="Sofa.Component.Topology.Container.Grid"/> <!-- Needed to use components [RegularGridTopology] -->
    <RequiredPlugin name="Sofa.Component.Visual"/> <!-- Needed to use components [VisualStyle] -->
    <RequiredPlugin name="Sofa.GL.Component.Rendering3D"/> <!-- Needed to use components [OglModel] -->

    <DefaultAnimationLoop/>
    <VisualStyle displayFlags="showBehaviorModels showForceFields showInteractionForceFields showVisual" />
    <CollisionPipeline verbose="0" />
    <BruteForceBroadPhase/>
    <BVHNarrowPhase/>
    <CollisionResponse name="Response" />
    <NewProximityIntersection alarmDistance="0.002" contactDistance="0.001" />
    <Node name="RotatingObstacle">
        <EulerExplicitSolver name="odesolver" printLog="false" />
        <MechanicalObject name="MS2" template="Rigid3" position="0 5 3 0 0 0 1" velocity="0 0 0 -0.1 0 0" />
        <UniformMass totalMass="1" />
        <PartialFixedProjectiveConstraint indices="0" fixedDirections="1 1 1 0 0 0" />
    </Node>
    <Node name="SquareCloth1">
        <EulerImplicitSolver name="odesolver" printLog="false"  rayleighStiffness="0.1" rayleighMass="0.1" />
        <CGLinearSolver iterations="25" name="linear solver" tolerance="1.0e-9" threshold="1.0e-9" />
        <MechanicalObject name="MS1" />
        <UniformMass totalMass="100" />
        <RegularGridTopology nx="20" ny="1" nz="20" xmin="12" xmax="-12" ymin="7" ymax="7" zmin="-12" zmax="12" />
        <BoxROI name="box1" box="-12 7 12 -10 7 12" />
        <FixedProjectiveConstraint indices="@box1.indices"/>
        <BoxROI name="box2" box="-12 7 12 -10 7 12" />
        <FixedProjectiveConstraint indices="@box2.indices"/>
        <MeshSpringForceField name="Springs" stiffness="2000" damping="0" />
        <QuadBendingSprings name="Bend" stiffness="20" damping="0" />
        <InteractionEllipsoidForceField template="Vec3,Rigid3" object1="@MS1" object2="@../RotatingObstacle/MS2" stiffness="1000" damping="1" center="0 0 0 0 -5 0" vradius="6 2 4   2 4 2" object2_forces="false" object2_invert="false" />
        <!--EllipsoidForceField stiffness="1000" damping="1" center="0 5 3" vradius="6 2 6" /-->
        <Node name="Visu">
            <OglModel name="Visual" color="green" />
            <IdentityMapping input="@.." output="@Visual" />
        </Node>
    </Node>
</Node>
```
```python
def createScene(rootNode):

	root = rootNode.addChild('root', gravity="0.0 -2.0 0.0", dt="0.04")
	root.addObject('RequiredPlugin', name="Sofa.Component.Collision.Detection.Algorithm")
	root.addObject('RequiredPlugin', name="Sofa.Component.Collision.Detection.Intersection")
	root.addObject('RequiredPlugin', name="Sofa.Component.Collision.Response.Contact")
	root.addObject('RequiredPlugin', name="Sofa.Component.Constraint.Projective")
	root.addObject('RequiredPlugin', name="Sofa.Component.Engine.Select")
	root.addObject('RequiredPlugin', name="Sofa.Component.LinearSolver.Iterative")
	root.addObject('RequiredPlugin', name="Sofa.Component.Mapping.Linear")
	root.addObject('RequiredPlugin', name="Sofa.Component.Mass")
	root.addObject('RequiredPlugin', name="Sofa.Component.MechanicalLoad")
	root.addObject('RequiredPlugin', name="Sofa.Component.ODESolver.Backward")
	root.addObject('RequiredPlugin', name="Sofa.Component.ODESolver.Forward")
	root.addObject('RequiredPlugin', name="Sofa.Component.SolidMechanics.Spring")
	root.addObject('RequiredPlugin', name="Sofa.Component.StateContainer")
	root.addObject('RequiredPlugin', name="Sofa.Component.Topology.Container.Grid")
	root.addObject('RequiredPlugin', name="Sofa.Component.Visual")
	root.addObject('RequiredPlugin', name="Sofa.GL.Component.Rendering3D")
	root.addObject('DefaultAnimationLoop')
	root.addObject('VisualStyle', displayFlags="showBehaviorModels showForceFields showInteractionForceFields showVisual")
	root.addObject('CollisionPipeline', verbose="0")
	root.addObject('BruteForceBroadPhase')
	root.addObject('BVHNarrowPhase')
	root.addObject('CollisionResponse', name="Response")
	root.addObject('NewProximityIntersection', alarmDistance="0.002", contactDistance="0.001")

	RotatingObstacle = root.addChild('RotatingObstacle')
	RotatingObstacle.addObject('EulerExplicitSolver', name="odesolver", printLog="false")
	RotatingObstacle.addObject('MechanicalObject', name="MS2", template="Rigid3", position="0 5 3 0 0 0 1", velocity="0 0 0 -0.1 0 0")
	RotatingObstacle.addObject('UniformMass', totalMass="1")
	RotatingObstacle.addObject('PartialFixedProjectiveConstraint', indices="0", fixedDirections="1 1 1 0 0 0")

	SquareCloth1 = root.addChild('SquareCloth1')
	SquareCloth1.addObject('EulerImplicitSolver', name="odesolver", printLog="false", rayleighStiffness="0.1", rayleighMass="0.1")
	SquareCloth1.addObject('CGLinearSolver', iterations="25", name="linear solver", tolerance="1.0e-9", threshold="1.0e-9")
	SquareCloth1.addObject('MechanicalObject', name="MS1")
	SquareCloth1.addObject('UniformMass', totalMass="100")
	SquareCloth1.addObject('RegularGridTopology', nx="20", ny="1", nz="20", xmin="12", xmax="-12", ymin="7", ymax="7", zmin="-12", zmax="12")
	SquareCloth1.addObject('BoxROI', name="box1", box="-12 7 12 -10 7 12")
	SquareCloth1.addObject('FixedProjectiveConstraint', indices="@box1.indices")
	SquareCloth1.addObject('BoxROI', name="box2", box="-12 7 12 -10 7 12")
	SquareCloth1.addObject('FixedProjectiveConstraint', indices="@box2.indices")
	SquareCloth1.addObject('MeshSpringForceField', name="Springs", stiffness="2000", damping="0")
	SquareCloth1.addObject('QuadBendingSprings', name="Bend", stiffness="20", damping="0")
	SquareCloth1.addObject('InteractionEllipsoidForceField', template="Vec3,Rigid3", object1="@MS1", object2="@../RotatingObstacle/MS2", stiffness="1000", damping="1", center="0 0 0 0 -5 0", vradius="6 2 4   2 4 2", object2_forces="false", object2_invert="false")

	Visu = SquareCloth1.addChild('Visu')
	Visu.addObject('OglModel', name="Visual", color="green")
	Visu.addObject('IdentityMapping', input="@..", output="@Visual")
```
<!-- automatically generated doc START -->
__Target__: Sofa.Component.MechanicalLoad

__namespace__: sofa::component::mechanicalload

__parents__: 
- ForceField

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
		<td>isCompliance</td>
		<td>
Consider the component as a compliance, else as a stiffness
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>rayleighStiffness</td>
		<td>
Rayleigh damping - stiffness matrix coefficient
</td>
		<td>0</td>
	</tr>
	<tr>
		<td>contacts</td>
		<td>
Vector of contacts
</td>
		<td></td>
	</tr>
	<tr>
		<td>center</td>
		<td>
ellipsoid center
</td>
		<td></td>
	</tr>
	<tr>
		<td>vradius</td>
		<td>
ellipsoid radius
</td>
		<td></td>
	</tr>
	<tr>
		<td>stiffness</td>
		<td>
force stiffness (positive to repulse outward, negative inward)
</td>
		<td>500</td>
	</tr>
	<tr>
		<td>damping</td>
		<td>
force damping
</td>
		<td>5</td>
	</tr>
	<tr>
		<td>color</td>
		<td>
ellipsoid color. (default=0,0.5,1.0,1.0)
</td>
		<td>0 0.5 1 1</td>
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



## Examples

```xml
<?xml version="1.0"?>
<!-- Mechanical EllipsoidForceField Example -->
<Node name="root" gravity="0.0 -2.0 0.0" dt="0.04">
    <RequiredPlugin name="Sofa.Component.Collision.Detection.Algorithm"/> <!-- Needed to use components [BVHNarrowPhase BruteForceBroadPhase CollisionPipeline] -->
    <RequiredPlugin name="Sofa.Component.Collision.Detection.Intersection"/> <!-- Needed to use components [NewProximityIntersection] -->
    <RequiredPlugin name="Sofa.Component.Collision.Geometry"/> <!-- Needed to use components [SphereCollisionModel] -->
    <RequiredPlugin name="Sofa.Component.Collision.Response.Contact"/> <!-- Needed to use components [CollisionResponse] -->
    <RequiredPlugin name="Sofa.Component.Constraint.Projective"/> <!-- Needed to use components [FixedProjectiveConstraint] -->
    <RequiredPlugin name="Sofa.Component.Engine.Generate"/> <!-- Needed to use components [MergeVectors] -->
    <RequiredPlugin name="Sofa.Component.Engine.Select"/> <!-- Needed to use components [BoxROI] -->
    <RequiredPlugin name="Sofa.Component.LinearSolver.Iterative"/> <!-- Needed to use components [CGLinearSolver] -->
    <RequiredPlugin name="Sofa.Component.Mapping.Linear"/> <!-- Needed to use components [IdentityMapping SubsetMapping] -->
    <RequiredPlugin name="Sofa.Component.Mass"/> <!-- Needed to use components [UniformMass] -->
    <RequiredPlugin name="Sofa.Component.MechanicalLoad"/> <!-- Needed to use components [EllipsoidForceField] -->
    <RequiredPlugin name="Sofa.Component.ODESolver.Backward"/> <!-- Needed to use components [EulerImplicitSolver] -->
    <RequiredPlugin name="Sofa.Component.SolidMechanics.Spring"/> <!-- Needed to use components [MeshSpringForceField QuadBendingSprings] -->
    <RequiredPlugin name="Sofa.Component.StateContainer"/> <!-- Needed to use components [MechanicalObject] -->
    <RequiredPlugin name="Sofa.Component.Topology.Container.Grid"/> <!-- Needed to use components [RegularGridTopology] -->
    <RequiredPlugin name="Sofa.Component.Visual"/> <!-- Needed to use components [VisualStyle] -->
    <RequiredPlugin name="Sofa.GL.Component.Rendering3D"/> <!-- Needed to use components [OglModel] -->

    <VisualStyle displayFlags="showForceFields showVisual" />
    <CollisionPipeline verbose="0" />
    <BruteForceBroadPhase/>
    <BVHNarrowPhase/>
    <CollisionResponse name="Response" />
    <NewProximityIntersection alarmDistance="0.002" contactDistance="0.001" />
    <DefaultAnimationLoop/>

    <Node name="SquareCloth1">
        <EulerImplicitSolver name="cg_odesolver" printLog="false"  rayleighStiffness="0.1" rayleighMass="0.1" />
        <CGLinearSolver iterations="25" name="linear solver" tolerance="1.0e-9" threshold="1.0e-9" />
        <MechanicalObject />
        <UniformMass totalMass="100" />
        <RegularGridTopology nx="20" ny="1" nz="20" xmin="12" xmax="-12" ymin="7" ymax="7" zmin="-12" zmax="12" />
        <BoxROI name="box1" box="-12 7 12 -10 7 12" />
        <BoxROI name="box2" box="10 7 12 12 7 12" />
        <MergeVectors template="Data<int>" name="mergedFixedIndices" nbInputs="2" input1="@box1.indices" input2="@box2.indices" />
        <FixedProjectiveConstraint name="ProjectiveFixedProjectiveConstraint" indices="@mergedFixedIndices.output" />
        
        <MeshSpringForceField name="Springs" stiffness="2000" damping="0" />
        <QuadBendingSprings name="Bend" stiffness="20" damping="0" />
        <EllipsoidForceField stiffness="1000" damping="1" center="0 5 3" vradius="6 2 6" />
        <!--		<EllipsoidForceField stiffness="-100" damping="0.1" center="0 10 3" vradius="20 10 20" color="1 0 0 1" />
		<PlaneForceField stiffness="1000" damping="20" normal="0 1 0" d="-3" /> -->
        <Node name="Visu">
            <OglModel name="Visual" color="green" />
            <IdentityMapping input="@.." output="@Visual" />
        </Node>
        <Node>
            <RegularGridTopology nx="4" ny="1" nz="4" xmin="12" xmax="-12" ymin="7" ymax="7" zmin="-12" zmax="12" />
            <MechanicalObject />
            <SphereCollisionModel radius="1.0" contactStiffness="1" />
            <SubsetMapping radius="0.8"/>
        </Node>
        <!--
		<Node name="Surf">
			<MechanicalObject />
			<RegularGridTopology
				nx="100" ny="1" nz="100"
				xmin="12" xmax="-12"
				ymin="7" ymax="7"
				zmin="-12" zmax="12" />
			<IdentityMapping />
			<TriangleCollisionModel />
		</Node>
		-->
    </Node>
</Node>
```
```python
def createScene(rootNode):

	root = rootNode.addChild('root', gravity="0.0 -2.0 0.0", dt="0.04")
	root.addObject('RequiredPlugin', name="Sofa.Component.Collision.Detection.Algorithm")
	root.addObject('RequiredPlugin', name="Sofa.Component.Collision.Detection.Intersection")
	root.addObject('RequiredPlugin', name="Sofa.Component.Collision.Geometry")
	root.addObject('RequiredPlugin', name="Sofa.Component.Collision.Response.Contact")
	root.addObject('RequiredPlugin', name="Sofa.Component.Constraint.Projective")
	root.addObject('RequiredPlugin', name="Sofa.Component.Engine.Generate")
	root.addObject('RequiredPlugin', name="Sofa.Component.Engine.Select")
	root.addObject('RequiredPlugin', name="Sofa.Component.LinearSolver.Iterative")
	root.addObject('RequiredPlugin', name="Sofa.Component.Mapping.Linear")
	root.addObject('RequiredPlugin', name="Sofa.Component.Mass")
	root.addObject('RequiredPlugin', name="Sofa.Component.MechanicalLoad")
	root.addObject('RequiredPlugin', name="Sofa.Component.ODESolver.Backward")
	root.addObject('RequiredPlugin', name="Sofa.Component.SolidMechanics.Spring")
	root.addObject('RequiredPlugin', name="Sofa.Component.StateContainer")
	root.addObject('RequiredPlugin', name="Sofa.Component.Topology.Container.Grid")
	root.addObject('RequiredPlugin', name="Sofa.Component.Visual")
	root.addObject('RequiredPlugin', name="Sofa.GL.Component.Rendering3D")
	root.addObject('VisualStyle', displayFlags="showForceFields showVisual")
	root.addObject('CollisionPipeline', verbose="0")
	root.addObject('BruteForceBroadPhase')
	root.addObject('BVHNarrowPhase')
	root.addObject('CollisionResponse', name="Response")
	root.addObject('NewProximityIntersection', alarmDistance="0.002", contactDistance="0.001")
	root.addObject('DefaultAnimationLoop')

	SquareCloth1 = root.addChild('SquareCloth1')
	SquareCloth1.addObject('EulerImplicitSolver', name="cg_odesolver", printLog="false", rayleighStiffness="0.1", rayleighMass="0.1")
	SquareCloth1.addObject('CGLinearSolver', iterations="25", name="linear solver", tolerance="1.0e-9", threshold="1.0e-9")
	SquareCloth1.addObject('MechanicalObject')
	SquareCloth1.addObject('UniformMass', totalMass="100")
	SquareCloth1.addObject('RegularGridTopology', nx="20", ny="1", nz="20", xmin="12", xmax="-12", ymin="7", ymax="7", zmin="-12", zmax="12")
	SquareCloth1.addObject('BoxROI', name="box1", box="-12 7 12 -10 7 12")
	SquareCloth1.addObject('BoxROI', name="box2", box="10 7 12 12 7 12")
	SquareCloth1.addObject('MergeVectors', template="Data<int>", name="mergedFixedIndices", nbInputs="2", input1="@box1.indices", input2="@box2.indices")
	SquareCloth1.addObject('FixedProjectiveConstraint', name="ProjectiveFixedProjectiveConstraint", indices="@mergedFixedIndices.output")
	SquareCloth1.addObject('MeshSpringForceField', name="Springs", stiffness="2000", damping="0")
	SquareCloth1.addObject('QuadBendingSprings', name="Bend", stiffness="20", damping="0")
	SquareCloth1.addObject('EllipsoidForceField', stiffness="1000", damping="1", center="0 5 3", vradius="6 2 6")

	Visu = SquareCloth1.addChild('Visu')
	Visu.addObject('OglModel', name="Visual", color="green")
	Visu.addObject('IdentityMapping', input="@..", output="@Visual")

	SquareCloth1 = SquareCloth1.addChild('SquareCloth1')
	SquareCloth1.addObject('RegularGridTopology', nx="4", ny="1", nz="4", xmin="12", xmax="-12", ymin="7", ymax="7", zmin="-12", zmax="12")
	SquareCloth1.addObject('MechanicalObject')
	SquareCloth1.addObject('SphereCollisionModel', radius="1.0", contactStiffness="1")
	SquareCloth1.addObject('SubsetMapping', radius="0.8")
```

<!-- automatically generated doc END -->
