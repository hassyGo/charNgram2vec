#pragma once

#include "Matrix.hpp"
#include "Rand.hpp"
#include "Vocabulary.hpp"

class SkipGram{
public:
  SkipGram(Vocabulary& voc_): voc(voc_){};

  Vocabulary& voc;
  Rand rndModel, rndData;
  MatD ngramVector;
  MatD scoreVector;

  int windowSize;
  int numNegative;

  std::vector<std::vector<Vocabulary::INDEX> > trainData;
  std::vector<std::vector<Vocabulary::INDEX> > devData;

  void init(const int dim, const int windowSize_, const int numNegative_, const std::string& trainFile, const bool train = true);
  void train(const Real learningRate);
  void save(const std::string& fileName);
  void load(const std::string& fileName);
private:
  void parse(const std::string& line, std::vector<Vocabulary::INDEX>& sentence);
  void train(const std::vector<Vocabulary::INDEX>& sentence, const Real learningRate);
  void train(const Vocabulary::INDEX target, const Vocabulary::INDEX context, const Real learningRate);
  void trainWord(const std::unordered_set<Vocabulary::INDEX>& ngram, const Vocabulary::INDEX context, const Real learningRate);
};
