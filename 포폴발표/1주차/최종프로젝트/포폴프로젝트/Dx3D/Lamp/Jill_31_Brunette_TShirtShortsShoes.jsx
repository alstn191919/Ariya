#target AfterEffects

/**************************************
Scene : Scene
Resolution : 1920 x 1080
Duration : 10.416667
FPS : 24.000000
Date : 2015-03-17 10:16:54.730479
Exported with io_export_after_effects.py
**************************************/



function compFromBlender(){

var compName = prompt("Blender Comp's Name \nEnter Name of newly created Composition","BlendComp","Composition's Name");
if (compName){
var newComp = app.project.items.addComp(compName, 1920, 1080, 1.000000, 10.416667, 24.000000);
newComp.displayStartTime = 0.083333;


// **************  CAMERA 3D MARKERS  **************


// **************  OBJECTS  **************


var _Jill_31_brunett_nude_Fhair01 = newComp.layers.addNull();
_Jill_31_brunett_nude_Fhair01.threeDLayer = true;
_Jill_31_brunett_nude_Fhair01.source.name = "_Jill_31_brunett_nude_Fhair01";
_Jill_31_brunett_nude_Fhair01.property("position").setValue([960.000000,540.000000,0.000000],);
_Jill_31_brunett_nude_Fhair01.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_Jill_31_brunett_nude_Fhair01.property("scale").setValue([100.000000,100.000000,100.000000],);


// **************  LIGHTS  **************


// **************  CAMERAS  **************


var _Camera = newComp.layers.addCamera("_Camera",[0,0]);
_Camera.autoOrient = AutoOrientType.NO_AUTO_ORIENT;
_Camera.property("position").setValue([1719.760094,823.061314,-968.580341],);
_Camera.property("orientation").setValue([-36.096345,-40.909179,-24.830890],);
_Camera.property("zoom").setValue(2100.000000,);



}else{alert ("Exit Import Blender animation data \nNo Comp's name has been chosen","EXIT")};}


app.beginUndoGroup("Import Blender animation data");
compFromBlender();
app.endUndoGroup();


