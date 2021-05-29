# Anomaly-Detection-WebApp
Advanced Programming 2 Project


### Summary
We implement a web-based interface for anomaly detection algorithms, actually a web page accessible from the browser in which the simple user can
upload a data file and discover the anomalies. The application supports linear regression algorithm and hybrid algorithm (with the minimum enclosing circle).
In addition, we implement a RESTful-API that is accessible on the network via an HTTP protocol and provides functions for calculating anomalies for 
potential customers, whether users of our app or external services. In this project we implement the MVC architecture.

### App Features
- [x] A RESTful API that uses HTTP requests to access and use data.
- [x] User can train or test a new model with one of the anomaly detection algorithms we have defined (regression or hybrid). Only CSV files with columns can be uploaded according to user needs
- [x] User Getting back a JSON which includes reporting where the anomalies occurred, and this JSON graphically displayed on the screen.

### Folder Structure
'''
├── Anomaly-Detection-WebApp
│   ├── src - cpp files used in calculations.
│   ├── build - contains the 'built' cpp files that can be used by our code.
|   ├── node_modules - contains the modules used to run the code.
|   ├── views - various configuration files.
|   ├── binding.gyp - a configuration file that is used to bind between cpp code and node js code.
|   ├── front-end.js - an js files that is responsible for the view portion of the code, in combination with the html file.
|   ├── index.html - the html file that is displayed when the user connects to the server.
|   ├── index.js - a general purpose debuging file.
|   ├── model.js - represent the model portion of the code.
|   ├── RESTfulAPI.js - a controller code portion of the code, is used in comunication between the server and the user.
|   ├── server.js - represents the server side that does calculations using the cpp files and gives responses back to the client.
|   └── various csv files - contains the files that may be used to run the code, the user can submit these files our any other files of their choosing.
'''

### Required installations
* Node.js 14.17.0 LTS ,Windows (x64)
* WebStorm 2021.1

### Compiling and Running
1. Download this repository.
2. Open WebStorm, and run server.js.
3. Run the server which listen on port: 9876.
4. Click on "train" or "test" buttons and upload CSV files. 
For "train" you need to upload a valid CSV file without anomalies, and for "test" you need to upload a CSV file - there may be anomalies in this file.

### Additional Links
