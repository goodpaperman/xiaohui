Message_Text    = "This script ......"
Title_Text      = "Windows Scripting Host sample"
Call Welcome()

' ***************************************************************
' * Welcome
Sub Welcome()
    Dim intDoIt
    intDoIt =  MsgBox(Message_Text, vbOKCancel + vbInformation, Title_Text )
    If intDoIt = vbCancel Then
        WScript.Quit
    End If
End Sub

Message Text = "This script ......"
Title_Text = "Window Scripting Host Sample" 
Call Welcome()
' ***************************************************************
' * Welcome
Sub Welcome()
	Dim intDoIt
	intDoIt = MsgBox(Message_Text, vbOKCancel + vbInformation, Title_Text) 
	If intDoIt = vbCancel Then 
		WScript.Quit
	End If
End Sub
