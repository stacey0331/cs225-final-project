# cs225-final-project

## Team
* Stacey Lee(staceyl2)
* Jianchen hong(jh104)
* Yanjie Han(yanjieh2)

## Quick start
When you have the right environment, in root directory:
```
cd open-flight && mkdir build && cd build && make && ./main
```

## How to run
### Environment Setup
#### 1) Install [Docker Desktop](https://www.docker.com/products/docker-desktop/)
And make sure to run Docker Desktop after installing.
#### 2) Install VS code extension [Remote - Containers](vscode:extension/ms-vscode-remote.remote-containers)
If you haven't download VS code, download it [here](https://code.visualstudio.com/download). 
#### 3) Run command "Remote-Container: Open Folder in Container"
By clicking the bottom left-hand corner green X-shaped button, or by pressing F1 and typing in the command (command + p in my mac)


### Prepare your code
In root directory: 
```
cd open-flight
mkdir build
cd build
```

Now run CMake as follows
```
cmake ..
```

### To compile and run main
After making sure you're in the build directory:
```
make && ./main
```