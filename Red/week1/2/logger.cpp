#include "test_runner.h"
#include <sstream>
#include <string>
using namespace std;

class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }
  void SetFile(const string& f){file=f;}
  void SetLine(const int& l){line=l;}
  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file= value; }

  void Log(const string& message);

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
  string file;
  int line;
};

void Logger::Log(const string& message){
	if(log_line&&log_file)
		os<<file<<":"<<to_string(line)<<" ";
	else if(log_file)
		os<<file<<" ";
	else if(log_line)
		os<<"Line "<<to_string(line)<<" ";
	os<<message<<endl;
}

#define LOG(logger, message) {	\
	logger.SetFile(__FILE__);	\
	logger.SetLine(__LINE__);	\
	logger.Log(message);		\
}

void TestLog() {
/* Р”Р»СЏ РЅР°РїРёСЃР°РЅРёСЏ СЋРЅРёС‚-С‚РµСЃС‚РѕРІ РІ СЌС‚РѕР№ Р·Р°РґР°С‡Рµ РЅР°Рј РЅСѓР¶РЅРѕ С„РёРєСЃРёСЂРѕРІР°С‚СЊ РєРѕРЅРєСЂРµС‚РЅС‹Рµ
 * РЅРѕРјРµСЂР° СЃС‚СЂРѕРє РІ РѕР¶РёРґР°РµРјРѕРј Р·РЅР°С‡РµРЅРёРё (СЃРј. РїРµСЂРµРјРµРЅРЅСѓСЋ expected РЅРёР¶Рµ). Р•СЃР»Рё
 * РјС‹ РґРѕР±Р°РІР»СЏРµРј РєР°РєРѕР№-С‚Рѕ РєРѕРґ РІС‹С€Рµ С„СѓРЅРєС†РёРё TestLog, С‚Рѕ СЌС‚Рё РЅРѕРјРµСЂР° СЃС‚СЂРѕРє РјРµРЅСЏСЋС‚СЃСЏ,
 * Рё РЅР°С€ С‚РµСЃС‚ РЅР°С‡РёРЅР°РµС‚ РїР°РґР°С‚СЊ. РС‚Рѕ РЅРµСѓРґРѕР±РЅРѕ.
 *
 * Р§С‚РѕР±С‹ СЌС‚РѕРіРѕ РёР·Р±РµР¶Р°С‚СЊ, РјС‹ РёСЃРїРѕР»СЊР·СѓРµРј СЃРїРµС†РёР°Р»СЊРЅС‹Р№ РјР°РєСЂРѕСЃ #line
 * (http://en.cppreference.com/w/cpp/preprocessor/line), РєРѕС‚РѕСЂС‹Р№ РїРѕР·РІРѕР»СЏРµС‚
 * РїРµСЂРµРѕРїСЂРµРґРµР»РёС‚СЊ РЅРѕРјРµСЂ СЃС‚СЂРѕРєРё, Р° С‚Р°РєР¶Рµ РёРјСЏ С„Р°Р№Р»Р°. Р‘Р»Р°РіРѕРґР°СЂСЏ РµРјСѓ, РЅРѕРјРµСЂР°
 * СЃС‚СЂРѕРє РІРЅСѓС‚СЂРё С„СѓРЅРєС†РёРё TestLog Р±СѓРґСѓС‚ С„РёРєСЃРёСЂРѕРІР°РЅС‹ РЅРµР·Р°РІРёСЃРёРјРѕ РѕС‚ С‚РѕРіРѕ, РєР°РєРѕР№
 * РєРѕРґ РјС‹ РґРѕР±Р°РІР»СЏРµРј РїРµСЂРµРґ РЅРµР№*/
#line 1 "logger.cpp"

  ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
}
