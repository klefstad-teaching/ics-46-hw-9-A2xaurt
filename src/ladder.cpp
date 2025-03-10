//ladder.cpp
#include "ladder.h"

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
//ladder Implementation

void verify_word_ladder() 
{

    set<string> word_list;

    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

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
    int* previousDistances=new int[size2+1];
    int* currentDistances=new int[size2+1];

    for(int i=0; i<=size2; ++i)
        previousDistances[i]=i;

    for(int i=0; i<size1; ++i)
    {
        currentDistances[0]=i+1;
        for(int a=0; a<size2; ++a)
        {
            int deletionCost=previousDistances[a+1]+1;
            int insertionCost=currentDistances[a]+1;
            int substitutionCost=previousDistances[a];
            if(str1[i]!=str2[a])
                ++substitutionCost;
            currentDistances[a+1]=min(deletionCost,min(insertionCost,substitutionCost));
        }
        swap_ranges(previousDistances,previousDistances+size2+1,currentDistances);
    }
    
    bool result=previousDistances[size2]<=d;
    delete[] previousDistances;
    delete[] currentDistances;
    return result;
}

bool is_adjacent(const string &word1, const string &word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list)
{
    //Currently does nothing to save time on the autograder so that I 
    //can see if some other changes to another function improved it or not
    /*
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
            if(is_adjacent(last_word,word)&&!visited.contains(word))
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
    */
    return {};
}