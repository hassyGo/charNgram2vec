#include "Vocabulary.hpp"
#include "Utils.hpp"
#include <iostream>

struct sort_pred {
  bool operator()(const std::pair<std::string, Vocabulary::COUNT> &left, const std::pair<std::string, Vocabulary::COUNT> &right) {
    return left.second > right.second;
  }
};

void Vocabulary::extractCharNgram(const std::string& str, std::unordered_map<std::string, Vocabulary::COUNT>& ngramCount){
  const std::string prefix = "#BEGIN#";
  const std::string suffix = "#END#";
  const unsigned int len = str.length();

  //unigram
  const std::string uni = "1gram-";
  for (unsigned int i = 0; i < len; ++i){
    const std::string entry = uni+str.substr(i, 1);
    auto it = ngramCount.find(entry);

    if (it == ngramCount.end()){
      ngramCount[entry] = 1;
    }
    else {
      it->second += 1;
    }
  }
  
  //bigram
  const std::string bi = "2gram-";
  for (unsigned int i = 0; i <= len; ++i){
    std::string entry;
    if (i == 0){
      entry = bi+prefix+str.substr(i, 1);
    }
    else if (i == len){
      entry = bi+str.substr(i-1, 1)+suffix;
    }
    else {
      entry = bi+str.substr(i-1, 2);
    }

    auto it = ngramCount.find(entry);
    if (it == ngramCount.end()){
      ngramCount[entry] = 1;
    }
    else {
      it->second += 1;
    }
  }

  //trigram
  const std::string tri = "3gram-";
  for (unsigned int i = 0; i < len; ++i){
    std::string entry;
    if (i == 0){
      if (len == 1){
	entry = tri+prefix+str+suffix;
      }
      else {
	entry = tri+prefix+str.substr(i, 2);
      }
    }
    else if (i == len-1){
      entry = tri+str.substr(i-1, 2)+suffix;
    }
    else {
      entry = tri+str.substr(i-1, 3);
    }

    auto it = ngramCount.find(entry);
    if (it == ngramCount.end()){
      ngramCount[entry] = 1;
    }
    else {
      it->second += 1;
    }
  }

  //fourgram
  if (len < 2){
    return;
  }
  const std::string four = "4gram-";
  for (unsigned int i = 0; i < len-1; ++i){
    std::string entry;
    if (i == 0){
      if (len == 2){
	entry = four+prefix+str+suffix;
      }
      else {
	entry = four+prefix+str.substr(i, 3);
      }
    }
    else if (i == len-2){
      entry = four+str.substr(i-1, 3)+suffix;
    }
    else {
      entry = four+str.substr(i-1, 4);
    }

    auto it = ngramCount.find(entry);
    if (it == ngramCount.end()){
      ngramCount[entry] = 1;
    }
    else {
      it->second += 1;
    }
  }
}

void Vocabulary::extractCharNgram(const std::string& str, std::unordered_set<Vocabulary::INDEX>& ngram){
  const std::string prefix = "#BEGIN#";
  const std::string suffix = "#END#";
  const unsigned int len = str.length();

  ngram.clear();

  //unigram
  const std::string uni = "1gram-";
  for (unsigned int i = 0; i < len; ++i){
    const std::string entry = uni+str.substr(i, 1);
    auto it = this->ngramIndex.find(entry);

    if (it == this->ngramIndex.end()){
      continue;
    }

    ngram.insert(it->second);
  }
  
  //bigram
  const std::string bi = "2gram-";
  for (unsigned int i = 0; i <= len; ++i){
    std::string entry;
    if (i == 0){
      entry = bi+prefix+str.substr(i, 1);
    }
    else if (i == len){
      entry = bi+str.substr(i-1, 1)+suffix;
    }
    else {
      entry = bi+str.substr(i-1, 2);
    }

    auto it = this->ngramIndex.find(entry);

    if (it == this->ngramIndex.end()){
      continue;
    }

    ngram.insert(it->second);
  }

  //trigram
  const std::string tri = "3gram-";
  for (unsigned int i = 0; i < len; ++i){
    std::string entry;
    if (i == 0){
      if (len == 1){
	entry = tri+prefix+str+suffix;
      }
      else {
	entry = tri+prefix+str.substr(i, 2);
      }
    }
    else if (i == len-1){
      entry = tri+str.substr(i-1, 2)+suffix;
    }
    else {
      entry = tri+str.substr(i-1, 3);
    }

    auto it = this->ngramIndex.find(entry);

    if (it == this->ngramIndex.end()){
      continue;
    }

    ngram.insert(it->second);
  }

  //fourgram
  if (len < 2){
    return;
  }
  const std::string four = "4gram-";
  for (unsigned int i = 0; i < len-1; ++i){
    std::string entry;
    if (i == 0){
      if (len == 2){
	entry = four+prefix+str+suffix;
      }
      else {
	entry = four+prefix+str.substr(i, 3);
      }
    }
    else if (i == len-2){
      entry = four+str.substr(i-1, 3)+suffix;
    }
    else {
      entry = four+str.substr(i-1, 4);
    }

    auto it = this->ngramIndex.find(entry);

    if (it == this->ngramIndex.end()){
      continue;
    }

    ngram.insert(it->second);
  }
}

Vocabulary::Vocabulary(const std::string& inputFile, const Vocabulary::COUNT wordFreqThreshold, const Vocabulary::COUNT nGramFreqThreshold){
  std::ifstream ifs(inputFile.c_str());
  std::vector<std::string> tokens;
  std::unordered_map<std::string, Vocabulary::COUNT> tokenCountMap;
  std::unordered_map<std::string, Vocabulary::COUNT> ngramCountMap;
  Vocabulary::COUNT totalCount = 0;

  std::cout << "Building the vocabulary..." << std::flush;

  for (std::string line; std::getline(ifs, line); ){
    if (line == ""){
      continue;
    }

    Utils::split(line, tokens);

    for (auto it = tokens.begin(); it != tokens.end(); ++it){
      //process ngrams
      this->extractCharNgram(*it, ngramCountMap);

      //process word
      auto it2 = tokenCountMap.find(*it);

      if (it2 == tokenCountMap.end()){
	tokenCountMap[*it] = 1;
      }
      else {
	tokenCountMap.at(*it) += 1;
      }
    }
  }

  //select frequent words
  for (auto it = tokenCountMap.begin(); it != tokenCountMap.end(); ++it){
    if (it->second >= wordFreqThreshold){
      this->tokenListCount.push_back(std::pair<std::string, Vocabulary::COUNT>(it->first, it->second));
    }

    totalCount += it->second;
  }
  this->unkIndex = this->tokenListCount.size();

  //select frequent ngrams
  for (auto it = ngramCountMap.begin(); it != ngramCountMap.end(); ++it){
    if (it->second >= nGramFreqThreshold){
      this->ngramListCount.push_back(std::pair<std::string, Vocabulary::COUNT>(it->first, it->second));
    }
  }

  //Sort by frequency
  std::sort(this->tokenListCount.begin(), this->tokenListCount.end(), sort_pred());
  std::sort(this->ngramListCount.begin(), this->ngramListCount.end(), sort_pred());

  for (Vocabulary::INDEX i = 0; i < this->tokenListCount.size(); ++i){
    this->tokenIndex[this->tokenListCount[i].first] = i;

    for (Vocabulary::COUNT j = 0, numNoise = (Vocabulary::COUNT)pow(this->tokenListCount[i].second, 0.75); j < numNoise; ++j){
      this->noiseDistribution.push_back(i);
    }
  }

  for (Vocabulary::INDEX i = 0; i < this->ngramListCount.size(); ++i){
    this->ngramIndex[this->ngramListCount[i].first] = i;
  }

  for (auto it = tokenListCount.begin(); it != this->tokenListCount.end(); ++it){
    this->discardProb.push_back((Real)it->second/totalCount);
    this->discardProb.back() = 1.0-sqrt(1.0e-05/this->discardProb.back());
  }

  std::vector<std::string>().swap(tokens);
  std::unordered_map<std::string, Vocabulary::COUNT>().swap(tokenCountMap);
  std::unordered_map<std::string, Vocabulary::COUNT>().swap(ngramCountMap);

  std::cout << " Done!" << std::endl;
}
