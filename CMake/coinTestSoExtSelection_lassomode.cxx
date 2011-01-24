#include <Inventor/nodes/SoExtSelection.h>
int
main ()
{

     SoExtSelection * sel = new SoExtSelection;
     sel->lassoMode = SoExtSelection::VISIBLE_SHAPES;
  ;
  return 0;
}
