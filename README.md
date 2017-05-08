# charNgram2vec
This repository provieds the re-implemented code for pre-training character n-gram embeddings presented in our Joint Many-Task (JMT) paper [1].
Compared with the original single-thread code used in the paper, in the new version, substantial speedup is achieved (e.g. asynchronous SGD).
Some pre-trained character n-gram embeddings are also available at <a href="http://www.logos.t.u-tokyo.ac.jp/~hassy/publications/arxiv2016jmt/">my project page</a>.

More details will come soon!

[1] <b>Kazuma Hashimoto</b>, Caiming Xiong, Yoshimasa Tsuruoka, and Richard Socher. 2016. A Joint Many-Task Model: Growing a Neural Network for Multiple NLP Tasks. <a href="https://arxiv.org/abs/1611.01587">arXiv cs.CL 1611.01587<a/>.

    @article{arXiv-2016-HASHIMOTO-jmt,
      Author =  {Hashimoto, Kazuma and Xiong, Caiming and Tsuruoka, Yoshimasa and Socher, Richard},
      Journal = {arXiv},
      Title =   {{A Joint Many-Task Model: Growing a Neural Network for Multiple NLP Tasks}},
      Volume =  {cs.CL 1611.01587},
      Year =    {2016},
      MONTH =   {November},
      URL   =   {http://arxiv.org/abs/1611.01587},
    }

## Licence ##
MIT licence
