#pragma once

#include <string>
#include <vector>

#ifndef HURDLESTATE_H
#define HURDLESTATE_H

class HurdleState {
 public:
  HurdleState(const std::string& answer)
      : answer_(answer), game_status_("active"), error_message_("") {}
  std::string GetAnswer() { return answer_; }
  void SetAnswer(const std::string& answer) {
    answer_ = answer;
  }
  std::vector<std::string> GetBoardColors() {
    return board_colors_;
  }
  void SetBoardColors(std::vector<std::string>& board_colors) {
    board_colors_ = board_colors;
  }
  std::vector<std::string> GetGuessedWords() {
    return guessed_words_;
  }
  void SetGuessedWords(const std::vector<std::string>& guessed_words) {
    guessed_words_ = guessed_words;
  }
  std::vector<std::string> GetLetterColors() {
    return letter_colors_;
  }
  void SetLetterColors(const std::vector<std::string> letter_colors) {
    letter_colors_ = letter_colors;
  }
  std::string GetGameStatus() { return game_status_; }
  void SetGameStatus(const std::string& game_status) {
    game_status_ = game_status;
  }
  // have to check the game status using a boolean function
  bool GameState() {
    if (game_status_ == "active") {
      return true;
    } else {
      return false;
    }
  }
  std::string GetErrorMessage() {
    return error_message_;
  }
  void SetErrorMessage(const std::string& error_message) {
    error_message_ = error_message;
  }

 private:
  std::string answer_;
  std::vector<std::string> board_colors_;
  std::vector<std::string> guessed_words_;
  std::vector<std::string> letter_colors_;
  std::string game_status_;
  std::string error_message_;
};

#endif
