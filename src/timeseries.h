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
    TimeSeries::TimeSeries(const map<string, string>& parsedJson);
    TimeSeries();


    int getNumOfRows();

    vector<float> &getColumnByProperyName(const string &propertyName) const;

    void insertPropertiesRow(const vector<string> &propertiesRow);

    const vector<string> &getPropertiesRow() const;

    void addRow(const vector<float> &row);

    float valueAtTime(const string &propertyName, int rowIndex) const;

    void loadFromCSVFile(string CSVfileName);

    void parseNames(const string& line);

    void parseLine(const string& line);

    void parseColumn(const string& line, const string& content);
};


#endif /* TIMESERIES_H_ */
