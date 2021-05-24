{
  "targets": [
    {
      "target_name": "anomalydetector",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/helloworld.cpp",
        "./src/index.cpp",
        "./src/anomaly_detection_util.cpp",
         "./src/CLI.cpp",
          "./src/HybridAnomalyDetector.cpp",
           "./src/minCircle.cpp",
            "./src/Server.cpp",
             "./src/SimpleAnomalyDetector.cpp",
              "./src/timeseries.cpp",


      ],
      "include_dirs": [
              "<!@(node -p \"require('node-addon-api').include\")"
            ],
      'dependencies': [
              "<!(node -p \"require('node-addon-api').gyp\")",
            ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}