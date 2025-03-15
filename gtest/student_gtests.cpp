#include <gtest/gtest.h>
#include <set>
#include "dijkstras.h"
#include "ladder.h"

// }TEST(Replace, Me) {
//   EXPECT_TRUE(false);


set<string> loadTestDictionary()
{
  set<string> wordlist;
  load_words(wordlist, "src/words.txt");
  return wordlist;
}

TEST(LadderTest, ValidLadder)
{
  set<string> wordlist = loadTestDictionary();
  vector<string> ladder = generate_word_ladder("cat", "dog", wordlist);
  ASSERT_EQ(ladder.size(), 4);
  EXPECT_EQ(ladder[0], "cat");
  EXPECT_EQ(ladder[1], "cot");
  EXPECT_EQ(ladder[2], "cog");
  EXPECT_EQ(ladder[3], "dog");
}

TEST(LadderTest, SameStartEndWord)
{
  set<string> wordlist = loadTestDictionary();
  vector<string> ladder = generate_word_ladder("cat", "cat", wordlist);
  ASSERT_TRUE(ladder.empty());
}

TEST(LadderTest, NoLadder)
{
  set<string> wordlist = loadTestDictionary();
  vector<string> ladder = generate_word_ladder("hello", "world", wordlist);
  ASSERT_TRUE(ladder.empty());
}

TEST(LadderTest, DifferentLengths)
{
  set<string> wordlist = loadTestDictionary();
  vector<string> ladder = generate_word_ladder("car", "cheat", wordlist);
  ASSERT_EQ(ladder.size(), 4);
  EXPECT_EQ(ladder[0], "car");
  EXPECT_EQ(ladder[1], "cat");
  EXPECT_EQ(ladder[2], "chat");
  EXPECT_EQ(ladder[3], "cheat");
}

TEST(LadderTest, EndWordNotIn)
{
  set<string> wordlist = loadTestDictionary();
  vector<string> ladder = generate_word_ladder("cat", "zzz", wordlist);
  ASSERT_TRUE(ladder.empty());
}

//Dijkstras TESTS

TEST(DijkstrasTest, Valid)
{
  Graph G;
  file_to_graph("src/small.txt", G);

  int source = 0;
  vector<int> previous(G.numVertices, -1);
  vector<int> distances = dijkstra_shortest_path (G, source, previous);
  EXPECT_EQ(distances[0], 0);
  EXPECT_EQ(distances[1], 3);
  EXPECT_EQ(distances[2], 6);
  EXPECT_EQ(distances[3], 1);

  vector<int> p1 = extract_shortest_path(distances, previous, 1);
  EXPECT_EQ(p1.size(), 3);
  EXPECT_EQ(p1[1], 0);
  EXPECT_EQ(p1[2], 3);
  EXPECT_EQ(p1[3], 1);
}

TEST(DijkstrasTest, SingleVertex)
{
  Graph G;
  file_to_graph("src/single_vertex.txt", G);

  int source = 0;
  vector<int> previous(G.numVertices, -1);
  vector<int> distances = dijkstra_shortest_path (G, source, previous);
  EXPECT_EQ(distances[0], 0);
}

TEST(DijkstrasTest, Disconnected)
{
  Graph G;
  file_to_graph("src/disconnected.txt", G);

  int source = 0;
  vector<int> previous(G.numVertices, -1);
  vector<int> distances = dijkstra_shortest_path (G, source, previous);
  EXPECT_EQ(distances[0], 0);
  EXPECT_EQ(distances[1], INF);
}

TEST(DijkstrasTest, NegWeight)
{
  Graph G;
  EXPECT_THROW(file_to_graph("src/negative_weights.txt", G), runtime_error);
}

TEST(DijkstrasTest, InvalidFile)
{
  Graph G;
  EXPECT_THROW(file_to_graph("src/invalid.txt", G), runtime_error);
}

