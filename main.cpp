#include <bits/stdc++.h>

#define FILEIN "/home/xander/Code/Cpp/FunnyFun/hepler/new.txt"
#define FILEOUT "/home/xander/Code/Cpp/FunnyFun/out.txt"

std::map<std::string, int> dictionary_words;
std::map<int, std::string> dictionary_ids;

int get(const std::string &key) { return dictionary_words[key]; }

std::string get(int key) { return dictionary_ids[key]; }

int getrandom(const std::vector<int> &values) {
  std::mt19937 gen(std::random_device{}());
  int sum = std::accumulate(values.begin(), values.end(), 0);

  std::uniform_int_distribution<int> dist(0, sum - 1);

  int x = dist(gen);

  int partial_sum = 0;
  int index = 0;
  for (; index < values.size(); ++index) {
    partial_sum += values[index];
    if (partial_sum > x) {
      break;
    }
  }

  return index;
}

void xander_ai(std::string word, int quantity,
               const std::vector<std::vector<int>> &vec) {
  std::ofstream output_file(FILEOUT);

  for (int i = 0; i < quantity; i++) {
    output_file << word << ' ';
    word = get(getrandom(vec[get(word)]));
  }
  output_file << word << '\n';
}

std::vector<std::vector<int>> get_dictionary() {
  std::string line;
  int index = -1;
  std::string prev_word;
  std::ifstream input_file(FILEIN);
  if (!input_file) {
    std::cout << "Problem!" << std::endl;
    exit(1);
  }

  while (std::getline(input_file, line)) {
    std::stringstream ss(line);
    std::string word;
    while (ss >> word) {
      if (dictionary_words.find(word) == dictionary_words.end()) {
        dictionary_words[word] = ++index;
        dictionary_ids[index] = word;
      }
    }
  }

  std::vector<std::vector<int>> vec(dictionary_words.size());
  for (int i = 0; i < dictionary_words.size(); i++) {
    vec[i].assign(dictionary_words.size(), 0);
  }

  input_file.close();
  input_file.open(FILEIN);

  while (std::getline(input_file, line)) {
    std::string word;
    std::stringstream ss(line);

    while (ss >> word) {
      if (!(prev_word.empty())) {
        vec[get(prev_word)][get(word)]++;
        // vec[get(prev_word)][get(word)]++;
      }
      prev_word = word;
    }
  }

  input_file.close();
  return vec;
}

void printVector2D(const std::vector<std::vector<int>> &vec) {
  for (const auto &row : vec) {
    for (const auto &element : row) {
      std::cout << element << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(0);

  auto vec = get_dictionary();

  xander_ai("дом", 100000, vec);

  return 0;
}
