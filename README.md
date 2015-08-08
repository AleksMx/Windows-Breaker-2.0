# Windows Breaker 2.0

This application can help you to restore access to your system.
For privilege elevation application uses CVE-2013-3660 vulnerability. It is work under Windows XP and not updated Vista, Server 2003-2012, Windows 7 and 8.

Many thanks:
 - Tavis Ormandy <taviso () cmpxchg8b com>
 - progmboy <programmeboy () gmail com>
for great description of this vulnerability.
  
Application author: Alexandr Mx
  

# Example
First of all build and run application on the system where you forgot your administrator password

![image](/images/1.png)
  
Click Start  
  
![image](/images/2.png)
  
After some time you will see cmd.exe process under SYSTEM user. If not please start again.  

![image](/images/3.png)
  
If you want to run Windows Explorer under SYSTEM user find it in the Task Manager and kill. Windows Desktop with all icons will be closed.  
  
![image](/images/4.png)
  
Then enter in the input "explorer" and click Start.  

![image](/images/5.png)
  
Great, now you can access files as the SYSTEM user.  

![image](/images/6.png)
  
Of course you can run pinball as the SYSTEM user and play!  
  
![image](/images/7.png)