#G.A.B.S.
##For our Project Tools Course at ELTE Faculty of Informatics

**Contributors**
    -Márk Kővári
    -Roland Szőke
    -Máté Szokolai


This repository contains our submission for the 'Project Tools' course.

Our goal was to make an application which would act as a workout planner and journal.

Features include:
    -Choosing from premade *Worksheet*s, which describe a workout plan.
        -The plans vary in length, difficulty and complexity.
        -All of these attributes are displayed to the user when they choose a *Worksheet*
    -Keeping a journal of the user's progress and completion of the chosen *Worksheet*
        -The user can complete a Workout, which consists of several predetermined exercises.
            -Notes can be assigned to each individual exercise.
            -Individual exercises can be marked skipped by not putting in it's parameters.
        -A Workout can be skipped, which will result in all of its exercises being skipped.

We have developed a solution which consists of the following layers:
    -The **Front-end layer**, the layer the user will be interacting with. This layer will be ran in a web browser, written in JavaScript and consuming the REST API the server layer provides.
        -*responsible : Roland Szőke*
    -The **Server layer**, which implements most of the business logic, provides the REST API and handles authentication. Written in C++ and using a HTTP framework, Pistache.
        -*responsible : Máté Szokolai*
    -The **Database layer**, which ensures data persistance and implements the database interface for the Server layer. TODO: what it uses
        -*responsible : Márk Kővári


**Note:** Do not use Chrome , POST requests are unreliable. Firefox works 100%.


Instructions for running the **Client** : 

````
cd client
 
npm i

npm start
````
This will only launch a webpack server, which **does not provide the REST API**
 
 
 Instructions for running the **Server** : 
 
 Install libraries : [libjwt](https://github.com/benmcollins/libjwt), [libnet from Pistache](https://github.com/oktal/pistache/) and [jansson](https://github.com/akheron/jansson) (usually available from default repositories)
 
 Install tools: `make, cmake, g++`

 If you wish to run the **test suite** install `gtest, gcov, lcov, genhtml`

 To generate the documentation, you will need `doxygen`
 
 If you are using Visual Code, just press `F5` to run the currently selected launcher or use the Launch and Task tools to select another.
 
 If not,
 ````
 mkdir build
 cd build
 cmake ..
 make $your_target
 ````
 The targets are:
    -Server
    -Test
    -coverage - to generate the test code coverage report (run the Test executable first)
    -doc - to generate the documentation
    -cleanup - to remove CMake's temporary files


 This will put the binary into `/build/bin` with the name `Server` or `Test`. Since Pistache only works on Linux, the server only works on Linux as well.
 
 You will also need to build the Client in order to serve it:
 
 ````
 cd client
 
 npm run build
 ````