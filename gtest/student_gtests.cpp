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

TEST(Ladder, print)
{
  beginCapture();
  print_word_ladder(vector<string>{"cat","cot","cog","bog","bag","bat"});
  EXPECT_EQ("Size: 6\ncat -> cot -> cog -> bog -> bag -> bat\n",captureResults());

  beginCapture();
  print_word_ladder(vector<string>{"cat","cot"});
  EXPECT_EQ("Size: 2\ncat -> cot\n",captureResults());

  beginCapture();
  print_word_ladder({});
  EXPECT_EQ("No path found!\n",captureResults());
}

TEST(Ladder, EditDistance)
{
  EXPECT_TRUE(edit_distance_within(string("cat"), string("cart"), 1));
  EXPECT_TRUE(edit_distance_within(string("cat"), string("carti"), 2));
  EXPECT_TRUE(edit_distance_within(string("cat"), string("carti"), 3));
  EXPECT_TRUE(edit_distance_within(string("cat"), string("ca"), 1));
  EXPECT_FALSE(edit_distance_within(string("cat"),string("carti"),1));
  EXPECT_TRUE(edit_distance_within(string("TimTim"), string("TomTomTim"), 5));
  EXPECT_TRUE(edit_distance_within(string("TimTim"), string("TomTom"), 2));
  EXPECT_TRUE(edit_distance_within(string("Tim"), string("TomTom"), 4));
  EXPECT_TRUE(edit_distance_within(string("cat"), string("barn"), 3));
  EXPECT_TRUE(edit_distance_within(string("timtim"), string("tomtomtim"), 4));
}

TEST(Ladder,isAdjacent)
{
  EXPECT_TRUE(is_adjacent(string("cat"), string("bat")));
  EXPECT_TRUE(is_adjacent(string("cat"), string("rat")));
  EXPECT_TRUE(is_adjacent(string("cat"), string("sat")));
  EXPECT_FALSE(is_adjacent(string("cat"), string("brat")));
  EXPECT_FALSE(is_adjacent(string("cat"), string("rats")));
  EXPECT_FALSE(is_adjacent(string("cat"), string("sate")));
  EXPECT_FALSE(is_adjacent(string("cat"), string("carts")));
}

TEST(Ladder,generateWordLadder)
{
  vector<string> ladder=generate_word_ladder("car", "cheat", {"cheat","cat","rat","chat","char","car","cog","dog"});
  EXPECT_EQ("car",ladder[0]);
  EXPECT_EQ("cat",ladder[1]);
  EXPECT_EQ("chat",ladder[2]);
  EXPECT_EQ("cheat",ladder[3]);
  EXPECT_EQ(4,ladder.size());
  vector<string> empty=generate_word_ladder("car", "bat",{"car","bat","run"});
  EXPECT_TRUE(empty.empty());
}