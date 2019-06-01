Enclosed is the source for a CPushPinFrame class. This class emulates the properties dialogs 
as seen in Microsoft Developer Studio. They sport a push pin button in the top left hand corner
which when unpinned automatically closes the property dialog when the dialog loses focus.
  The MS implementation seems to use custom draw controls which seems a shame when you lose 
all the functionality provided by the MFC property sheet classes.
  The class of interest is CPushPinFrame and is derived from CFrameWnd. It provides a look which
is similar to the modal MFC property sheets. You must create one on the heap and you then attach a 
property sheet to it by using the SetAttachedProperySheet method. This method uses CRuntimeClass 
so your propery sheet will need DYNCREATE attributes. For further details on how you should setup 
one in your application have a look at CPushPinSheetDlg::OnProperties() in the demo program.
  You will also need to pull down the CPushPin class from my web site and copy in the pushpin.cpp 
and pushpin.h files from that archive. The bitmaps CPushPin uses are already in the demo program.


Enjoy,

16th April 1998
PJ Naughter,
email: pjn@indigo.ie
web: http://indigo.ie/~pjn
