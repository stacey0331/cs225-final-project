# cs225-final-project

## Team
* Stacey Lee(staceyl2)
* Jianchen hong(jh104)
* Yanjie Han(yanjieh2)

## Presensation Video
* Unlisted in Youtube [here](https://youtu.be/zY1RODBWK1w)

## Repo Structure
* Major code and algorithms are in [`/open-flight/src`](https://github.com/stacey0331/cs225-final-project/tree/master/open-flight/src)
* Datasets are in [`/open-flight/dataset`](https://github.com/stacey0331/cs225-final-project/tree/master/open-flight/dataset)
* Written report, project proposal, and team contracts are in [`/open-flight/docs`](https://github.com/stacey0331/cs225-final-project/tree/master/open-flight/docs)


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
Instructions to use this program will appear in the terminal after it's compiled and run successfully. 

## Run Test Cases
In root directory (after creating /build and run cmake):
```
cd open-flight
cd build
make && ./test
```