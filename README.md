# Markov Chain

## Parts of the project:
### markov
* generates table of token ids
* generate table of automaton transitions
#### command line invocation
* markov <file with urls> <context len> <prefix for dict and index files>

### generator
* generate random sequences

#### command line invocation
* generator <prefix for dict and index files> <context file>

#### context file format
* context length
* number of sequences to generate
* repeated:
  * len of sequence to generate
  * [token1, token2, ...]

### File structure of the project :
* bin - binary programs files
* common_code - shared between markov and generator files
* data:
 * test data and "War and Peace" file
 * configuration files for markov
 * test data files:
   * hello_test_0{1,2,3}.txt - text files for a small obvious model training
 * configuration files for markov
   * ars.txt - uri for the old narod site
   * bash.txt - uri for jokes site
   * local.uri - take files from localhost provided by python server
* generator - main part of the generator program
* markov - main part of the markov program
* models - trained models of the Markov chain generator

## How to start local python server:
* python2: python -m SimpleHTTPServer
* python3: python -m http.server

## Model files format:
### Tokes file format
* records number
* token id

### Table of automaton transitions format:
* context length
* number of contexts
* context_id
  * number of known for this context tokens
    * token_id frequency
