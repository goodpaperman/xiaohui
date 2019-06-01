Animated Icon on Titlebar of a window 

-----------------------------------------------------------------------
This article was contributed by Rajesh Parikh. 
 

Introduction:

This simple class is for people who want to make their application more attractive using icon animation in the title bar of frame window. 

Technique: 

All the consecutive images used for animation are stored in a single bitmap resource. The animation could have been achieved also by storing each image as separate icon in the resource, but that would have made managing them more difficult. Putting the images as a list of image also makes it easier to keep track of the sequence of animation. 

To start with the class loads the bitmap resource in a CImageList using CimageList::Create function. Then whenever ShowNextImage is called the class loads the image using CimageList::ExtractIcon and displays it in title bar by sending WM_SETICON to the frame window. 

Usage: 

1. Add AnimateIcon.cpp and AnimateIcon.h files in your project. 

2. Create a bitmap resource and put all the images (16 pixels x 16 pixels) in the desired sequence. 



3. Add #include "AnimateIcon.h" at the beginning of your mainframe.h file.

4. Add the following protected members to your mainframe class 


    CAnimateIcon m_animIcon;
    UINT m_timerID;
5. Add the following code in OnCreate member of your frame class 

    m_animIcon.SetImageList(IDB_ANIM_IMGLIST,4,RGB(0,0,0));
    m_timerID = this->SetTimer(99,500,NULL);
SetImageList takes 3 parameters pass ID of your bitmap resource created in step 2 as first parameter. The second parameter is the no of (16x16) images in your bitmap, which is 4 in our case. The last parameter is the RGB value of color you want to make transparent. Second line of code sets a new timer. Here I have made it to fire every 500 ms. you can change it to suit your animation speed. 
6. Create a OnDestroy()handler for your main frame class and add the following code. This is very important because if you do not kill the timer created you will lose system resources. 


    CFrameWnd::OnDestroy();
    if(m_timerID != 0)
        KillTimer(m_timerID);
7. Add WM_TIMERhandler to your frame class and add the following code 


    m_animIcon.ShowNextImage();
Compile and run the code. Now you should be able to see your window icon being animated. Note that just adding the above code also would bring up default MFC icon for a moment. If you want to avoid this change the IDR_MAINFRAME icon in the resource. 

Note: 

The sample project is built using Visual C++ 4.1, and has been tested on Visual C++ versions 4.1 and 6.0. If you directly try to run the .exe in the sample project it may ask for VC 4.1 runtime DLLs. 

Download demo project - 46 KB 

Download source - 2 KB 

Date Posted: October 30, 1998 
