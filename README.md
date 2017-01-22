# PICN Framework
Written by Zeinab Zali, Ehsan Aslanian
January 2016

#How to use

1- Please execute seeker and client packages on separate machines in a LAN (a seeker machine and arbitrary number of and clients).

2- QT5.4 libraries are required. It is recommended to open the projects (.pro files) with QT creator and run the packages via this editor.

3- Please pay attention that the Data folder (with its all subfolders) is required for client and Log folder is required for seeker in the    execution folder.

4- Firefox browser has been tested now with the client package, but any other browser can be used. It is sufficient to set the proxy IP      for the browser to 127.0.0.1:6060. 

5- Please pay attention that https requests may cause the client crash.

6- For extracting the diagrams from log files you can use Matlab files in the folder Matlab.
   In order to use matlab files place the log file (log.txt) of the client in Matlab/log folder and then execute:                            CDF_Vectors('log.txt')

