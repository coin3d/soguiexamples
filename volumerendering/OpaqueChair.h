
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/nodes/SoClipPlane.h>
#include <Inventor/nodes/SoText2.h>

#include <SmallChange/nodekits/SmAxisKit.h>
#include <VolumeViz/nodes/SoOrthoSlice.h>

class OpaqueChair {

  SoSeparator * opaquechairroot;

  SoOrthoSlice * bottominsideorthoslice;
  SoOrthoSlice * leftinsideorthoslice;
  SoOrthoSlice * backinsideorthoslice;

  SoTranslation * leftclipplanetrans;
  SoTranslation * bottomclipplanetrans;
  SoTranslation * backclipplanetrans;

  SoTranslation * axisxlabeltrans;
  SoTranslation * axisylabeltrans;
  SoTranslation * axiszlabeltrans;

  SoText2 * axisxlabel;
  SoText2 * axisylabel;
  SoText2 * axiszlabel;

  SoFieldSensor * draggerXSensor;
  SoFieldSensor * draggerYSensor;
  SoFieldSensor * draggerZSensor;

  float draggerXRange;
  float draggerYRange;
  float draggerZRange;

  SbVec3f volumedims;
  SbVec3s volumeslices;

  void loadInventorFile();
  void setupDraggers();
  void setupGeometry();
  void setupAxisMarkers(SmAxisKit * kit, float start, float stop, float interval);

  static void draggerXCB(void * data, SoSensor * sensor);
  static void draggerYCB(void * data, SoSensor * sensor);
  static void draggerZCB(void * data, SoSensor * sensor);

public:
  OpaqueChair(const char * filename);
  ~OpaqueChair();
  
  SbBool loadVolumeData(const char * filename);
  SoSeparator * getSceneGraph();
  void setXAxisRange(float start, float stop, float interval);
  void setYAxisRange(float start, float stop, float interval);
  void setZAxisRange(float start, float stop, float interval);
  
};
