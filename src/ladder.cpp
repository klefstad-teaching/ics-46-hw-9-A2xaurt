//ladder.cpp
#include "ladder.h"
#include "timer.h"

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
//ladder Implementation

void verify_word_ladder() 
{
    Timer t;
    double eTime;
    set<string> word_list;

    load_words(word_list, "src/words.txt");

    t.start();
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    t.elapsedUserTime(eTime);
    cout<<"Time: "<<eTime<<endl;

    t.start();
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    t.elapsedUserTime(eTime);
    cout<<"Time: "<<eTime<<endl;

    t.start();
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    t.elapsedUserTime(eTime);
    cout<<"Time: "<<eTime<<endl;

    t.start();
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    t.elapsedUserTime(eTime);
    cout<<"Time: "<<eTime<<endl;

    t.start();
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    t.elapsedUserTime(eTime);
    cout<<"Time: "<<eTime<<endl;

    t.start();
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
    t.elapsedUserTime(eTime);
    cout<<"Time: "<<eTime<<endl;

}

void error(string word1, string word2, string msg)
{
    cout<<"Error: "<<word1<<msg<<word2<<endl;
}

void load_words(set<string> &word_list, const string &file_name)
{
    word_list.clear();
    ifstream in{file_name};
    if (in)
        for (string word; in >> word; )
            word_list.insert(word);
    else
        error("",file_name,"Unable to find input file at file name- ");
}

void print_word_ladder(const vector<string> &ladder)
{
    int size=ladder.size();
    if(size==0)
        cout<<"No word ladder found."<<endl;
    else
    {
        cout<<"Word ladder found: ";
        for(int i=0; i<size; ++i)
            cout<<ladder[i]<<' ';
        cout<<endl;
    }
}

bool edit_distance_within(const std::string &str1, const std::string &str2, int d)
{
    int size1=str1.size();
    int size2=str2.size();
    vector<vector<int>> distances(size1+1,vector<int>(size2+1,0));

    //cout<<"First assignment!"<<endl;
    for(int i=1; i<=size1; ++i)
        distances[i][0]=i;

    //cout<<"Second assignment!"<<endl;
    for(int i=1; i<=size2; ++i)
        distances[0][i]=i;

    //cout<<"Starting nest!"<<endl;
    for(int i=1; i<=size1; ++i)
        for(int a=1; a<=size2; ++a)
        {
            int substitutionCost=0;
            //cout<<"Checking str1[i] and str2[a]!"<<endl;
            if(str1[i]!=str2[a])
                ++substitutionCost;
            //cout<<"Assigning distance!"<<endl;
            distances[i][a]=min(distances[i-1][a]+1,min(distances[i][a-1]+1,distances[i-1][a-1]+substitutionCost));
        }

    //cout<<"Attempting return!"<<endl;
    return distances[size1-1][size2-1]<=d;

}

bool is_adjacent(const string &word1, const string &word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list)
{
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty())
    {
        vector<string> ladder=ladder_queue.front();
        ladder_queue.pop();
        string last_word=ladder.back();
        for(string word : word_list)
        {
                if(is_adjacent(last_word,word))
                {
                    if(!visited.contains(word))
                    {
                        visited.insert(word);
                        vector<string> new_ladder=ladder;
                        new_ladder.push_back(word);
                        if(word==end_word)
                            return new_ladder;
                        ladder_queue.push(new_ladder);
                    }
                }
        }
    }

    return {};
}