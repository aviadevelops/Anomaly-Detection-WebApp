// Author: Aviad Saadi, ID: 212330567

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <vector>
#include <map>
#include <string>

using namespace std;

class TimeSeries {

    map<string, vector<float>> propertyNamesToColumns;
    vector<string> propertiesRow;
    int numOfRows;

    const vector<float> &getColumn(const string &propertyName) const;


public:
    TimeSeries(string CSVfileName);
    TimeSeries();


    int getNumOfRows();

    void putCopyOfColumn(const string &propertyName, vector<float> &columnCopy) const;

    void insertPropertiesRow(const vector<string> &propertiesRow);

    const vector<string> &getPropertiesRow() const;

    void addRow(const vector<float> &row);

    float valueAtTime(const string &propertyName, int rowIndex) const;

    void loadFromCSVFile(string CSVfileName);

};


#endif /* TIMESERIES_H_ */
