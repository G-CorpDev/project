# project
For Project Tools at ELTE IK


Instructions for **Client** : 

`cd client`
 
` npm i `

 `npm start`
 
 
 Instructions for **Server** : 
 
 Install libraries : [libjwt](https://github.com/benmcollins/libjwt) and [libnet from Pistache](https://github.com/oktal/pistache/)
 
 Install tools: `make, cmake, g++`
 
 If you are using Visual Code, just press `F5` or use the Launch and Task tools.
 
 If not, `mkdir build`
 
 `cd build`
 `cmake ..`
 `make`
 
 This will put the binary into `/build/bin` with the name `Server`. Since Pistache only works on Linux, this only works on Linux as well.
 

