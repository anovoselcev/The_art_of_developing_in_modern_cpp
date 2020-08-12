#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<int> MONTH_LENGTHS =
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int MONTH_COUNT = MONTH_LENGTHS.size();

int main() {
  int q;
  cin >> q;

  int month = 0;
  
  vector<vector<string>> days_concerns(MONTH_LENGTHS[month]);

  for (int i = 0; i < q; ++i) {
    string operation_code;
    cin >> operation_code;

    if (operation_code == "ADD") {

      int day;
      string concern;
      cin >> day >> concern;
      --day;
      days_concerns[day].push_back(concern);

    } else if (operation_code == "NEXT") {

      const int old_month_length = MONTH_LENGTHS[month];
      
      month = (month + 1) % MONTH_COUNT;
      
      const int new_month_length = MONTH_LENGTHS[month];
      
      if (new_month_length < old_month_length) {
        
        vector<string>& last_day_concerns = days_concerns[new_month_length - 1];
        
        for (int day = new_month_length; day < old_month_length; ++day) {
          last_day_concerns.insert(
              end(last_day_concerns),
              begin(days_concerns[day]), end(days_concerns[day]));
        }
      }
      days_concerns.resize(new_month_length);

    } else if (operation_code == "DUMP") {

      int day;
      cin >> day;
      --day;
      
      cout << days_concerns[day].size() << " ";
      for (const string& concern : days_concerns[day]) {
        cout << concern << " ";
      }
      cout << endl;

    }
  }

  return 0;
}
