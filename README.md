--------------------------------------------------------------------------------
README.md file for CS 3360 Programming Assignment 2

Student: Kayla Vincent, jqg8
Date: 10/29/2024

This README file describes requirements and execution instructions to compile
and run Programming Assignment 2 for Dr. Kecheng Yang's Computing Systems
Fundamentals course in the fall of 2024. 

--------------------------------------------------------------------------------

Table of Contents:
     1. Requirements
     2. Execution Instructions
     3. Condensed Execution Instructions

Requirements: 

The proper tools and environments needed to run Problems 1 and 2 are:

     Server: Texas State University Linux server; zeus.cs.txstate.edu
     FileZilla: file transfer system to upload source code to the Linux server
     Command Line: terminal or command line to connect to the Linux server

Execution Instructions:

Download files: 
     Download appropriate source code file: PA2_Vincent.cpp 

Upload files to FileZilla:
     Log into the desired Linux server using your credentials (username and 
     password), the name of the server (zeus.cs.txstate.edu), and port 22. This
     will connect you to the Texas State Linux server. Drag and drop the files
     downloaded in the previous step to the "Remote Site" section.

Connect to the Linux Server:
     Using the command line, execute the following command:
     ssh netID@zeus.cs.txstate.edu
     Replacing "netID" with your netID, and then filling in the corresponding 
     password. 

Navigate to proper directory:
     Navigate to the directory the file was uploaded to in the upload step using
     cd commands

Compile and execute the program:
     To compile and run Problem 1, execute the following:
          g++ -o a2.out PA2_Vincent.cpp
          ./a2.out

Condensed Execution Instructions:
     g++ -o a2.out PA1_Vincent.cpp
     ./a2.out

The source code file for Programming Assignment 2 should run as intended if these steps are followed correctly.
