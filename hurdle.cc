#include "hurdle.h"

#include "hurdlestate.cc"
#include "hurdlestate.h"

void HurdleGame::NewHurdle() {
  hurdle_state_ = HurdleState(hurdlewords_.GetRandomHurdle());
}
std::string CheckBoardColors(std::string guessed_words, std::string answer) {
  std::string board_color_check = "BBBBB";
  for (int i = 0; i < answer.size(); i++) {
    if (guessed_words[i] == answer[i]) {
      board_color_check[i] = 'G';
      answer[i] = '$';
    }
  }
  for (int i = 0; i < answer.size(); i++) {
    if (answer.find(guessed_words.at(i)) != std::string::npos) {
      int index = answer.find(guessed_words.at(i));
      if (board_color_check[i] != 'G') {
        board_color_check = 'Y';
        answer[index] = '$';
      }
    }
  }
  return board_color_check;
}
void HurdleGame::LetterEntered(char key) {
  if (hurdle_state_.GetGameStatus() != "active") {
    return;
  }
  hurdle_state_.SetErrorMessage("");
  std::vector<std::string> guessed_words = hurdle_state_.GetGuessedWords();
  if (guessed_words.size() == 0) {
    guessed_words.push_back("");
  }
  int idx = guessed_words.size() - 1;
  std::string word = guessed_words.at(idx);
  if (word.size() != 5) {
    guessed_words[idx] = word + key;
    hurdle_state_.SetGuessedWords(guessed_words);
  }
}
void HurdleGame::WordSubmitted() {
  std::vector<std::string> guessed_words = hurdle_state_.GetGuessedWords();
  if (hurdle_state_.GetGameStatus() != "active") {
    return;
  }
  hurdle_state_.SetErrorMessage("");
  int index = guessed_words.size() - 1;
  std::string word = guessed_words.at(index);
  if (word.length() != 5) {
    hurdle_state_.SetErrorMessage("Not enough letters!");
    return;
  } else if (!hurdlewords_.IsGuessValid(word)) {
    hurdle_state_.SetErrorMessage("Not a valid word!");
    return;
  }
  std::string board_colors = CheckBoardColors(word, hurdle_state_.GetAnswer());
  std::vector<std::string> board_col = hurdle_state_.GetBoardColors();
  board_col.push_back(board_colors);
  hurdle_state_.SetBoardColors(board_col);
  std::string ans = hurdle_state_.GetAnswer();
  if (board_colors == "GGGGG") {
    hurdle_state_.SetGameStatus("win");
  } else if (guessed_words.size() == 6) {
    hurdle_state_.SetGameStatus("lose");
  } else {
    guessed_words.push_back("");
    hurdle_state_.SetGuessedWords(guessed_words);
  }
}
void HurdleGame::LetterDeleted() {
  std::vector<std::string> current_guess = hurdle_state_.GetGuessedWords();
  if (current_guess.size() == 0 || (hurdle_state_.GetGameStatus() != "active")) {
    return;
  }
  int index = current_guess.size() - 1;
  std::string word = current_guess.at(index);
  if (word.length() == 0) {
    return;
  }
  word.pop_back();
  current_guess.at(index) = word;
  hurdle_state_.SetGuessedWords(current_guess);
}

crow::json::wvalue HurdleGame::JsonFromHurdleState() {
  // The JSON object to return to the Hurdle Frontend.
  crow::json::wvalue hurdle_state_json({});

  // ===================== YOUR CODE HERE =====================
  // Fill the hurdle_state_json with the data expected by the
  // Hurdle frontend. The frontend expects the following keys:
  //   1. "answer"
  hurdle_state_json["answer"] = hurdle_state_.GetAnswer();
  //   2. "boardColors"
  hurdle_state_json["boardColors"] = hurdle_state_.GetBoardColors();
  //   3. "guessedWords"
  hurdle_state_json["guessedWords"] = hurdle_state_.GetGuessedWords();
  //   4. "gameStatus"
  hurdle_state_json["gameStatus"] = hurdle_state_.GetGameStatus();
  //   5. "errorMessage"
  hurdle_state_json["errorMessage"] = hurdle_state_.GetErrorMessage();
  //   6. [OPTIONAL] "letterColors"
  hurdle_state_json["letterColors"] = hurdle_state_.GetLetterColors();

  return hurdle_state_json;
}
