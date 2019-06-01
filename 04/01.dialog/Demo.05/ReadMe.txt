	Many times you may want to allow your users to see a preview of the file
that they are about to open. CPreviewFileDialog does just that.

	The only work that you will have to do is to write a class derived
from CAbstractPreview . Two functions will have to be implemented in this
class. 

	SetPreviewFile(const CString& csFileName) -
		This function is called each time the user changes his selection.
This method allows you to open the file and get things ready for painting it
in the Open File Dialog ( and yes , you can use it for a save Dialog also).
		Keep in mind that the file name passed may not be a valid one.
For eg: if the user chooses a directory, you will get the name of the
directory. It is upto you to decide how you want this case handled.

	DrawPreview(CDC *pDC,int x,int y,int width,int height) -
		This routine will be called to actually paint the image. The
DC which is sent is not clipped. You will have to make sure that you
keep within the bounds. The preview is shown on the right hand side
of the window. By default, the width and height of the preview window
are 100 bytes. You may want to draw on a smaller scale . Or, more often
, you may have to scale your view to the smallest fitting rectangle.
You can call the routine Calc for this. Pass it the width and height
of your original view and the window width and height passed to you.
You will get a CRect which centres your view.


	One more small thing ! The sample project contains a dialog called
"FILEOPEN_TEMPLATE". You will have to copy this into your project
resource file. 

	Also , please do not forget to include CPreviewFileDialog.cpp in 
your project. I`m aware that the file name has an extra C prefixed,
but I had to rename it as it was conflicting with some of my older
projects which are in the include path.

	In every other way, use CPreviewFileDialog exactly as you would
CFileDialog. Just pass its constructor a pointer to a class derived
from CAbstractPreview. 

	CPreviewFileDialg also provides a checkbox the user can use to 
disable the preview feature.

	The files to look at in the sample are CTestPreviewDoc -
		take a look at OnFileOpen...

	I have used a support class called CDIB to handle Device Independent
Bitmaps. You are free to use it , but let me warn you , no comments
in the code and no formal help from me. Be warned also, that it is meant
primarily for 8 bit bitmaps. If you have a doubt ,
mail me rrajivram@hotmail.com and I`ll try to help.

	Have a look at the sample and happy previewing.

