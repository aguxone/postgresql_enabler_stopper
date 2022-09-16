
# PostgreSQL Enabler-Stopper

## Description
Using PostgreSQL only sporadically for some of your projects? With PostgreSQL Enabler-Stopper you can disable the posgresSQL server running in the background with one click.
The application will automatically detect the postgreSQL service on windows and disable it for you (you can define the service you want to enable or disable).
Only compatible with Windows at the time being, but it will become cross-platform in the future.
<!-- ![screen-gif](./prueba_rando_creator.gif) -->
<!-- <img src="https://github.com/aguxone/agux_random_file_creator/blob/gif_storage/prueba_rando_creator.gif?raw=true" alt="agxu_rfc_gif" width="60%" height="40%"> -->
<img src="https://github.com/aguxone/postgresql_enabler_stopper/blob/gif-storage-branch/500x341_15fps.gif?raw=true" alt="postgresql_es_gif" width="70%" height="40%">
<!-- <video src='https://user-images.githubusercontent.com/98858551/174418629-481619d3-27ed-48c0-b952-05b6239417b3.mp4'; width="100"; height="100"></video> -->
<!-- https://user-images.githubusercontent.com/98858551/174418629-481619d3-27ed-48c0-b952-05b6239417b3.mp4 -->
<!-- <video  style="display:block; width:10%; height:auto;" autoplay controls loop="loop">
       <source src=https://user-images.githubusercontent.com/98858551/174418629-481619d3-27ed-48c0-b952-05b6239417b3.mp4 type="video/mp4" />
</video> -->
<!-- <div style="width:100px ; height:100px>
       <video src='https://user-images.githubusercontent.com/98858551/174418629-481619d3-27ed-48c0-b952-05b6239417b3.mp4'></video>
<div/> -->

## Libraries/Languages used
- C++
- WxWidgets 3.2.0
- Windows CMD console

## Usage:
- Run the executable file with admin rights (it needs to disable the postgresql service), you can download one on the release section.
- Optional: Write the service name exactly you want to enable/stop on service on the service_file_name.ini file.
- Use the "Try to find service and save it to ini file" to automatically search for a postgreSQL service on your system and write to te ini file.
- Use the "Check Status" button to check the status of the service of the service specified on the ini file.
- Use "Start" and "Stop" button to initialize or stop the service saved on the ini file.

## Compilation from source:
You can easily compile this app (if you have already used wxWidgets before) with the included makefiles "dynamic.makefile" and "static.makefile". If you compile your app dynamically you'll have to include the dynamic libraries wxbase32u_gcc_custom.dll and wxmsw32u_core_gcc_custom.dll in the same folder of the .exe file.
The makefiles are made so that the required files files are present in the following direcotires (typically 2 folders up):
dynamic.makefile

. wxWidgets include folder:

       ../../librerias_cpp/wx_3_2_0/include
       ../../librerias_cpp/wx3_2_0/lib_release_dynamic/mswu
       
. wxWidgets library folder:

       ../../librerias_cpp/wx3_2_0/lib_release_dynamic
       
. resources folder and file:

       ./resources/resources.rc

static.makefile

. wxWidgets include folder:

       ../../librerias_cpp/wx_3_2_0/include
       
       ../../librerias_cpp/wx3_2_0/lib_release_static/mswu
       
. wxWidgets library folder:

       ../../librerias_cpp/wx3_2_0/lib_release_dynamic
       
. resources folder and file:

       ./resources/resources.rc


If you are new to wxWidgets, you must first compile the wxWidgets library one time with YOUR compiler or use the released binaries that matches exactly the version of your compiler (in my case i compiled mine, i used the MinGW compiler version 11.2.0 compiled by Brecht Sanders https://www.winlibs.com/); know that you must compile a "dynamic" version and/or "static" version of the library according to your needs. Here's a guide for windows users, although they are basically the same steps for others OSs using "make" https://moritzmolch.com/blog/2510.html. If you are using for example code-blocks as your ide, to today's date it commes with a default compiler which is the old mingw gcc version 8.1.0 (a popular version) and there are binaries of wxWidgets already available for this version on their main site.
Once you have your libraries (basically 2 include folders and one lib folder) on the right folders, you just run the makefile from console or script:

       mingw32-make static.makefile

Or the dyanamic.makefile and your executable is ready to use.
You can compress with UPX to reduce the size to a third.
