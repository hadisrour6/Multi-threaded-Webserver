# C++ Multi-Threaded Web Server  
A multi-threaded web server built in C++, capable of handling multiple client requests simultaneously, serving static web pages, and logging requests efficiently.  

## About  
This project was created to explore multi-threading, networking, and server development in C++. The goal was to build a lightweight, efficient HTTP web server that can handle multiple concurrent connections using a custom thread pool, serve static HTML/CSS pages, log all requests & errors to a file and database, support GET & POST requests, and provide a foundation for REST API development. 

## Features  
Multi-Threaded – Uses a custom thread pool to handle multiple clients efficiently. Static File Hosting – Serves HTML, CSS, JS, and other static files. GET & POST Support – Handles basic API requests. Logging System – Logs all requests & errors to a file for debugging. SQLite Database – Stores request logs in a database for analysis. Configurable Settings – Modify server settings dynamically via server_config.json.  

## Technical Documentation  

### System Requirements
- **Operating System:** Linux, macOS, or Windows (WSL/MinGW)
- **Compiler:** GCC (g++) with C++11 or later

### Dependencies  
g++ (C++11 or later), 
make, 
pthread (POSIX Threads), 
sqlite3, 
libsqlite3-dev, 
iostream, 
fstream,  
sstream, 
vector, 
queue, 
mutex, 
thread, 
condition_variable

### Installation  
To run the web server locally

1. clone the repository -> ```sh  
git clone https://github.com/yourusername/Cpp-MultiThreaded-WebServer.git  
cd Cpp-MultiThreaded-WebServer ```

2. Build and run the server using Makefile
```make```

3. After successful compilation run:
```./server```

5. To test server, go to:
http://localhost:8080

### Configuration
Configure server_config.json to change the server settings. 

##Results
The multi-threaded server was tested using 100 concurrent clients, showing a 40% performance improvement compared to a single-threaded implementation.

## Author & Date 
- Author: [@hadisrour6](https://www.github.com/hadisrour6)
- Version: 1.0.0 
- Date: January 12, 2025 
