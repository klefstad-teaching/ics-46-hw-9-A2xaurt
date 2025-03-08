#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

//A helper to begin taking in output
void beginCapture()
{
  testing::internal::CaptureStdout();
}

//A helper to return what was captured from the output
string captureResults()
{
  return testing::internal::GetCapturedStdout();
}

TEST(Ladder, loadWords)
{
  set<string> words;
  EXPECT_EQ(0,words.size());
  beginCapture();
  load_words(words, "fakeyFakey123");
  EXPECT_EQ("Error: Unable to find input file at file name- fakeyFakey123\n",captureResults());
  EXPECT_EQ(0,words.size());
  beginCapture();
  load_words(words, "src/words.txt");
  EXPECT_EQ("",captureResults());
  EXPECT_EQ(45392,words.size());
  load_words(words, "src/small.txt");
  EXPECT_EQ(7,words.size());
}
