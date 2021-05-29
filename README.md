# Anomaly-Detection-WebApp
Advanced Programming 2 Project


### Summary
We have implemented a web-based interface for anomaly detection algorithms - a web page accessible from the browser in which a user can
upload data files and discover anomalies in the data. The application supports two anomaly detection algorithms - a simple algorithm based on linear regression, as well as a hybrid one, combining regression with finding the minimum enclosing circle containing the data points. The user can choose and switch between the algorithms as they wish. 
In addition, we have implemented a RESTful-API that is accessible via HTTP protocol, and provides functionality for communicating with the anomaly detection server, both for users of our app or external services. 
The web app was built using the MVC architecture.

### App Features
- [x] A RESTful API that uses HTTP requests to access and use data.
- [x] User can train or test a new model with one of the anomaly detection algorithms we have defined (regression or hybrid). Only CSV files with columns can be uploaded according to user needs.
- [x] User gets back a JSON which includes reporting of the anomalies occurred, as well as graphic display of the anomalic data points.

### Folder Structure


### Required installations
* Node.js 14.17.0 LTS, Windows (x64)

### Running The App
1. Download this repository.
2. Run "node server.js" through the command line, or otherwise run the server.js file using a working enviorment.
3. The server will then start running on the local host machine. The server listens on port 8080.
4. Open the web application using a browser of your choice, by entering the URL http://localhost:8080
5. Upload a .csv file for training your model using the "upload train CSV" button. Then, upload a .csv file in which you would like to find anomalies using the "upload test CSV" button. Choose an anomaly detection algorith from the corresponding list.
6. Press "detect anomalies" and wait for the calculations to complete. The anomalic data points will appear both as text and as red points in the graph - you can hold your cursor on such a point to see it's values.

### Using the API
External users can use our implemented RESTful-API to communicate with the anomaly detection server without the need of using the web application. This can be used, for example, for automating the process of detecting anomalies in data regulary. The API contains the following functions:
1. GET /api/model (model_id): returns JSON of given model, if it exists on the server.
2. GET /api/models: returns JSON of all models currently on server.
3. GET /api/features (model_id): returns JSON of list of features from given model, if it exists on the server.
4. POST /api/model (model_type): adds new model to the server.
5. POST /api/anomaly (model_id): detects anomalies in given model and returns them as JSON.
6. DELETE /api/model (model_id): deletes given model from server.

### Additional Links
- [UML Diagram](uml_fixed.png)
