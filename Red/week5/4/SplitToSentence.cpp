#include "../../TestRunner/test_runner.h"

#include <vector>

using namespace std;

// РћР±СЉСЏРІР»СЏРµРј Sentence<Token> РґР»СЏ РїСЂРѕРёР·РІРѕР»СЊРЅРѕРіРѕ С‚РёРїР° Token
// СЃРёРЅРѕРЅРёРјРѕРј vector<Token>.
// Р‘Р»Р°РіРѕРґР°СЂСЏ СЌС‚РѕРјСѓ РІ РєР°С‡РµСЃС‚РІРµ РІРѕР·РІСЂР°С‰Р°РµРјРѕРіРѕ Р·РЅР°С‡РµРЅРёСЏ
// С„СѓРЅРєС†РёРё РјРѕР¶РЅРѕ СѓРєР°Р·Р°С‚СЊ РЅРµ РјР°Р»РѕРїРѕРЅСЏС‚РЅС‹Р№ РІРµРєС‚РѕСЂ РІРµРєС‚РѕСЂРѕРІ,
// Р° РІРµРєС‚РѕСЂ РїСЂРµРґР»РѕР¶РµРЅРёР№ вЂ” vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// РљР»Р°СЃСЃ Token РёРјРµРµС‚ РјРµС‚РѕРґ bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
	vector<Sentence<Token>> result;
	Sentence<Token> sent;
	bool f = false;
	for(auto& x : tokens){
		if(!x.IsEndSentencePunctuation()&&!f){
			sent.push_back(move(x));
		}
		else if(x.IsEndSentencePunctuation()){
			f = true;
			sent.push_back(move(x));
		}
		else if(!x.IsEndSentencePunctuation()&&f){
			f = false;
			result.push_back(move(sent));
			sent.clear();
			sent.push_back(move(x));
		}
	}
	if(!sent.empty())
		result.push_back(move(sent));
	return result;
}


struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

// РўРµСЃС‚ СЃРѕРґРµСЂР¶РёС‚ РєРѕРїРёСЂРѕРІР°РЅРёСЏ РѕР±СЉРµРєС‚РѕРІ РєР»Р°СЃСЃР° TestToken.
// Р”Р»СЏ РїСЂРѕРІРµСЂРєРё РѕС‚СЃСѓС‚СЃС‚РІРёСЏ РєРѕРїРёСЂРѕРІР°РЅРёР№ РІ С„СѓРЅРєС†РёРё SplitIntoSentences
// РЅРµРѕР±С…РѕРґРёРјРѕ РЅР°РїРёСЃР°С‚СЊ РѕС‚РґРµР»СЊРЅС‹Р№ С‚РµСЃС‚.
void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
