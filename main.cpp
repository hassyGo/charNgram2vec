#include "Vocabulary.hpp"
#include "SkipGram.hpp"
#include "Utils.hpp"
#include <iostream>

int main(int argc, char** argv){
  int dim = 100;
  int windowSize = 1;
  int numNegative = 15;
  Real learningRate = 0.025;
  int wordFreqThreshold = 10;
  int nGramFreqThreshold = 10;
  std::string trainFile = "./sample_data/sample.txt";
  std::string outputFile = "./result";

  Utils::procArg(argc, argv,
		 dim, windowSize, numNegative, learningRate,
		 wordFreqThreshold, nGramFreqThreshold,
		 trainFile, outputFile);

  printf("### Settings ###\n");
  printf("-edim      %d\n", dim);
  printf("-window    %d\n", windowSize);
  printf("-neg       %d\n", numNegative);
  printf("-lr        %f\n", learningRate);
  printf("-wminfreq  %d\n", wordFreqThreshold);
  printf("-cminfreq  %d\n", nGramFreqThreshold);
  printf("-train     %s\n", trainFile.c_str());
  printf("-output    %s\n", outputFile.c_str());
  puts("");

  Vocabulary voc;
  SkipGram sg(voc);
  
  voc = Vocabulary(trainFile, wordFreqThreshold, nGramFreqThreshold);
  std::cout << "Word vocabulary size:\t" << voc.tokenListCount.size() << std::endl;
  std::cout << "Ngram Vocabulary size:\t" << voc.ngramListCount.size() << std::endl;

  sg.init(dim, windowSize, numNegative, trainFile, true);
  sg.train(learningRate);

  std::cout << "Done!" << std::endl;

  sg.save(outputFile);

  return 0;
}
