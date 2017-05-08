#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include "Matrix.hpp"

class Vocabulary{
public:

  typedef unsigned int INDEX;
  typedef unsigned long int COUNT;

  Vocabulary(){};
  Vocabulary(const std::string& inputFile, const Vocabulary::COUNT wordFreqThreshold, const Vocabulary::COUNT nGramFreqThreshold);

  std::unordered_map<std::string, Vocabulary::INDEX> tokenIndex;
  std::vector<std::pair<std::string, Vocabulary::COUNT> > tokenListCount;
  Vocabulary::INDEX unkIndex;

  std::unordered_map<std::string, Vocabulary::INDEX> ngramIndex;
  std::vector<std::pair<std::string, Vocabulary::COUNT> > ngramListCount;

  std::vector<Vocabulary::INDEX> noiseDistribution;
  std::vector<Real> discardProb;

  void extractCharNgram(const std::string& str, std::unordered_set<Vocabulary::INDEX>& ngram);

private:
  void extractCharNgram(const std::string& str, std::unordered_map<std::string, Vocabulary::COUNT>& ngramCount);
};
